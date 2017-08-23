#include "all_included.h"

int What_Program_Doing_While_Import;
int Is_Load_Start = FALSE;

DB * Start_Import_Process()
{
	DB * root = NULL;
	FILE * file_gate;
	fopen_s(&file_gate,LOAD_FILE_NAME, "rb");
	
	if (Is_File_Exists(file_gate) == YES)
	{
		root = Import_File_and_Store_to_Memory(file_gate);
		fclose(file_gate);
	}
	else
	{
		root = (DB*)malloc(sizeof(DB));
		memset(root, 0, sizeof(DB));
	}
	printf("���� : help\n");
	if (root == NULL)
	{
		printf("Start_Import_Process() �������� ���� ����!\n");
		exit(0);
	}
	return root;
}

DB * Import_File_and_Store_to_Memory(FILE * file_gate)
{
	DB * root = (DB*)malloc(sizeof(DB));
	memset(root, 0, sizeof(DB));

	int file_size = Get_File_Size(file_gate);
	char buffer[COMMON_LENGTH] = { 0 };
	char byte;
	for (int i = 0; i < file_size; i++)
	{	//������ '1����Ʈ ��' �о ���� ���� �������� �����Ѵ�.
		fread(&byte, ONE_BYTE, ONCE, file_gate);
		Decoding_Byte(&byte);
		switch (Judge_Operator(byte))
		{
		case STORE_NORMAL_DATA_TO_THE_BUFFER:
			if (Is_Load_Start == FALSE)
				continue;
			else
				Store_to_Buffer(buffer, byte);
			break;
		case WAIT_FOR_OPERATION_NUMBER:
			break;
		case INPUT_DATA_FROM_NOW:
			break;
		case PASS_BUFFER_TO_PROPER_POSITION:
			if (Is_Load_Start == FALSE)
				continue;
			if (NO_STRING_INPUT(buffer))	//�ƹ��͵� ������ �� ���ϴϱ� NULL�̶�� ǥ�ö� ����.
				strcpy_s(buffer, COMMON_LENGTH, NULL_MESSAGE);
			Pass_Buffer_to_Proper_Position(buffer, root);
#if IMPORT_DEBUG
			printf("[%s] < Ȯ��\n", buffer);
#endif
			memset(buffer,0,COMMON_LENGTH);
			break;
		default:
			break;
		}
	}
	printf("\n����� DB �� %d ���� ����Ʈ�� �����Ѵ�.\n", root->how_many_sites);
	return root;
}
int Judge_Operator(char byte)	//�Ű������� ���޹��� byte�� �ؼ��Ͽ� ���� ����� �������� ��ȯ�Ѵ�.
{
	static char is_operation_mode = FALSE;
	if (is_operation_mode == FALSE)
		if (byte == START_OP)
		{
			is_operation_mode = TRUE;
			return WAIT_FOR_OPERATION_NUMBER;
		}
		else if (byte == END_OP || byte == EMPTY_OP)
			return PASS_BUFFER_TO_PROPER_POSITION;		//byte���� ���۸� ������ ��ġ�� ������.
		else
			return STORE_NORMAL_DATA_TO_THE_BUFFER;//byte�� END_OP�ų� EMPTY_OP�� ������ ��� �׾Ƶд�.
	else //if(*is_operation_mode == TRUE)
	{
		if (is_digit_char(byte) != FALSE)
		{
#if IMPORT_DEBUG
			printf("\n[op %c] ", byte);
#endif
			switch (byte)
			{
			case START_PROGRAM:
#if IMPORT_DEBUG
				printf("�ҷ��� ���� ������ ���� �Է� ����.\n");
#endif
				Is_Load_Start = TRUE;
				break;
			case INPUT_SITE_NAME:
#if IMPORT_DEBUG
				printf("�α��� ��� ������ ���� ����.\n");
#endif
				break;
			case INPUT_ACCOUNT_ID:
#if IMPORT_DEBUG
				printf("ID ���� ����.\n");
#endif
				break;
			case INPUT_ACCOUNT_PW:
#if IMPORT_DEBUG
				printf("PW ���� ����.\n");
#endif
				break;
			case INPUT_ACCOUNT_CURRENT_UPDATE:
#if IMPORT_DEBUG
				printf("������Ʈ �ð� ���� ����.\n");
#endif
				break;
			case INPUT_ACCOUNT_MEMO:
#if IMPORT_DEBUG
				printf("������ ���� �޸� ���� ����.\n");
#endif
				break;
			case END_INPUT_SITE:
#if IMPORT_DEBUG
				printf("�α��� ��� ������ ���� ����.\n");
#endif
				break;
			case END_PROGRAM:
#if IMPORT_DEBUG
				printf("�ҷ��� ��� ���� ������ ���� �Է� ����.\n");
#endif
				Is_Load_Start = FALSE;
				break;
			default:
				printf("����ġ ���� ���� (��� ��ȣ ����)\n");
			}
		}
		What_Program_Doing_While_Import = byte;
		is_operation_mode = FALSE;
		return INPUT_DATA_FROM_NOW;
	}
}
void Pass_Buffer_to_Proper_Position(char buffer[COMMON_LENGTH], DB * root)
{	//���ۿ� ���� ���ڿ��� ��� ��ġ�� ������? -> �������� What_data_program_loading�� ����
	static Site_Account * SA;
	static Account_Element * AE;

	switch (What_Program_Doing_While_Import)
	{
	case INPUT_SITE_NAME:	//SA�� �����Ǿ����� ����Ʈ �̸��� �Բ� �̸� DB�� ���δ�.
		SA = (Site_Account*)malloc(sizeof(Site_Account));
		strcpy_s(SA->Site_Name, SITE_NAME_LENGTH, buffer);
		SA->next = NULL;		//�������� �����ϱ� ������ ����
		SA->head = NULL;	//���� �� ����Ʈ ������ ����������� ���� ���� ���� ����.
		SA->how_many_accounts = 0;
		Attach_SA_to_the_DB(SA, root);
		break;
	case INPUT_ACCOUNT_ID:	//AE�� �ʿ��� �Է��� �������� �̸� SA�� ���δ�. �� �Ŀ� õõ�� �ʱ�ȭ�� ������.
		AE = (Account_Element*)malloc(sizeof(Account_Element));
		Attach_AE_to_the_SA(AE, SA);
		strcpy_s(AE->ID, ID_LENGTH, buffer);
		break;
	case INPUT_ACCOUNT_PW:
		strcpy_s(AE->PW, PASSWORD_LENGTH, buffer);
		break;
	case INPUT_ACCOUNT_CURRENT_UPDATE:
		strcpy_s(AE->Update_Time, UPDATE_TIME_SIZE, buffer);
		break;
	case INPUT_ACCOUNT_MEMO:
		strcpy_s(AE->Memo, MEMO_LENGTH, buffer);
		AE->next = NULL;
		AE = NULL;
		break;
	case END_INPUT_SITE:
		SA = NULL;
	}
}
int Is_File_Exists(FILE * file_gate)
{
	char select;
	if (file_gate == NULL)
	{
		printf("���� ������ ���� ������ �������� �ʴµ�, ��� �ұ��?\n");
		printf("���� ������� n ��, �����Ϸ��� q �� �����ּ���.\n");
		do
		{
			select = (char)_getch();
		} while (select != 'n' &&  select != 'q');
		switch (select)
		{
		case 'n':
			break;
		case 'q':
			printf("����!\n");
			exit(0);
		}
		return NO;
	}
	else
		return YES;
}
int Get_File_Size(FILE * fp)
{
	int file_size;
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return file_size;
}
void Decoding_Byte(char * byte)
{
#if ACTIVE_DECODING
	(*byte) ^= START_OP;
#endif
#if IMPORT_DEBUG
#if SHOW_DECODING_PROCESS
	SET_COLOR(DARK_YELLOW);
	printf("%c", (*byte));
	SET_COLOR_DEFAULT;
#endif
#endif
}
void Store_to_Buffer(char buffer_to_store_byte[COMMON_LENGTH], const char byte_will_stored_to_buffer)
{
	for (int i = 0; i < COMMON_LENGTH; i++)
		if (buffer_to_store_byte[i] == 0)
		{
			buffer_to_store_byte[i] = byte_will_stored_to_buffer;
			return;
		}
	printf("����! ���� ũ�Ⱑ %d�� �ʰ���.\n", COMMON_LENGTH);
	return;
}