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
	printf("도움말 : help\n");
	if (root == NULL)
	{
		printf("Start_Import_Process() 과정에서 적재 실패!\n");
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
	{	//파일을 '1바이트 씩' 읽어서 무슨 일을 수행할지 결정한다.
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
			if (NO_STRING_INPUT(buffer))	//아무것도 없으면 좀 허하니까 NULL이라는 표시라도 넣자.
				strcpy_s(buffer, COMMON_LENGTH, NULL_MESSAGE);
			Pass_Buffer_to_Proper_Position(buffer, root);
#if IMPORT_DEBUG
			printf("[%s] < 확정\n", buffer);
#endif
			memset(buffer,0,COMMON_LENGTH);
			break;
		default:
			break;
		}
	}
	printf("\n적재된 DB 는 %d 개의 사이트를 포함한다.\n", root->how_many_sites);
	return root;
}
int Judge_Operator(char byte)	//매개변수로 전달받은 byte을 해석하여 무슨 명령을 수행할지 반환한다.
{
	static char is_operation_mode = FALSE;
	if (is_operation_mode == FALSE)
		if (byte == START_OP)
		{
			is_operation_mode = TRUE;
			return WAIT_FOR_OPERATION_NUMBER;
		}
		else if (byte == END_OP || byte == EMPTY_OP)
			return PASS_BUFFER_TO_PROPER_POSITION;		//byte쌓인 버퍼를 적절한 위치로 보낸다.
		else
			return STORE_NORMAL_DATA_TO_THE_BUFFER;//byte가 END_OP거나 EMPTY_OP일 때까지 계속 쌓아둔다.
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
				printf("불러올 파일 정보에 따라 입력 시작.\n");
#endif
				Is_Load_Start = TRUE;
				break;
			case INPUT_SITE_NAME:
#if IMPORT_DEBUG
				printf("로그인 대상 페이지 적재 시작.\n");
#endif
				break;
			case INPUT_ACCOUNT_ID:
#if IMPORT_DEBUG
				printf("ID 적재 시작.\n");
#endif
				break;
			case INPUT_ACCOUNT_PW:
#if IMPORT_DEBUG
				printf("PW 적재 시작.\n");
#endif
				break;
			case INPUT_ACCOUNT_CURRENT_UPDATE:
#if IMPORT_DEBUG
				printf("업데이트 시각 적재 시작.\n");
#endif
				break;
			case INPUT_ACCOUNT_MEMO:
#if IMPORT_DEBUG
				printf("계정에 대한 메모 적재 시작.\n");
#endif
				break;
			case END_INPUT_SITE:
#if IMPORT_DEBUG
				printf("로그인 대상 페이지 적재 종료.\n");
#endif
				break;
			case END_PROGRAM:
#if IMPORT_DEBUG
				printf("불러온 모든 파일 정보에 따른 입력 종료.\n");
#endif
				Is_Load_Start = FALSE;
				break;
			default:
				printf("예기치 못한 오류 (명령 번호 에러)\n");
			}
		}
		What_Program_Doing_While_Import = byte;
		is_operation_mode = FALSE;
		return INPUT_DATA_FROM_NOW;
	}
}
void Pass_Buffer_to_Proper_Position(char buffer[COMMON_LENGTH], DB * root)
{	//버퍼에 들어온 문자열을 어느 위치에 놓을까? -> 전역변수 What_data_program_loading를 참조
	static Site_Account * SA;
	static Account_Element * AE;

	switch (What_Program_Doing_While_Import)
	{
	case INPUT_SITE_NAME:	//SA가 생성되었으니 사이트 이름과 함께 이를 DB에 붙인다.
		SA = (Site_Account*)malloc(sizeof(Site_Account));
		strcpy_s(SA->Site_Name, SITE_NAME_LENGTH, buffer);
		SA->next = NULL;		//마지막에 붙으니까 다음은 없고
		SA->head = NULL;	//이제 막 사이트 정보가 만들어졌으니 계정 정보 또한 없다.
		SA->how_many_accounts = 0;
		Attach_SA_to_the_DB(SA, root);
		break;
	case INPUT_ACCOUNT_ID:	//AE에 필요한 입력이 끝났으니 이를 SA에 붙인다. 그 후에 천천히 초기화해 나간다.
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
		printf("계정 정보를 담은 파일이 존재하지 않는데, 어떻게 할까요?\n");
		printf("새로 만들려면 n 을, 종료하려면 q 를 눌러주세요.\n");
		do
		{
			select = (char)_getch();
		} while (select != 'n' &&  select != 'q');
		switch (select)
		{
		case 'n':
			break;
		case 'q':
			printf("종료!\n");
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
	printf("에러! 버퍼 크기가 %d을 초과함.\n", COMMON_LENGTH);
	return;
}