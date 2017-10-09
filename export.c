#include "all_included.h"

void Export_DB(DB * root)
{
	system("cls");
	int is_something_changes = History_Show();
	if (is_something_changes == FALSE)
		BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(���� ����));
	if (Ask_Continue("���� ���� ���� ������ �����Ͻðڽ��ϱ�?") == FALSE)
		BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(���� ����));
	FILE * file_gate;
	fopen_s(&file_gate, EXPORT_FILE_NAME, "wb");
	if (file_gate == NULL)
	{
		printf("Export() ����!");
		return;
	}
	Site_Account * SA = root->first_Site;
	Account_Element * AE = NULL;
	unsigned char buffer[COMMON_LENGTH] = { 0 };
	Delay_n_Second_and_Print_Dots(EXPORT_DELAY_SEC);
	srand((unsigned)time(NULL));

#if ACTIVE_ENCODING
#if GENERATE_JUNK_BYTE
	Write_Random_Byte(file_gate, LOOK_NORMALLY_CHAR,	MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, ALPHABET_ONLY,				MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, DIGIT_ONLY,						MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, ALPHABET_ONLY,				MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, DIGIT_ONLY,						MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, ALPHABET_ONLY,				MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
#endif
#endif
	Write_Operator(file_gate, START_OP, START_PROGRAM);
	while (SA != NULL)
	{
		Write_Operator(file_gate, START_OP, INPUT_SITE_NAME);
		Wrtie_String(file_gate, SA->Site_Name);
		Write_Operator(file_gate, END_OP, (char)NULL);
		AE = SA->head;
		while (AE != NULL)
		{
			Write_Operator(file_gate, START_OP, INPUT_ACCOUNT_ID);	//������ ID ����
			Wrtie_String(file_gate, AE->ID);
			Write_Operator(file_gate, END_OP, (char)NULL);

			Write_Operator(file_gate, START_OP, INPUT_ACCOUNT_PW);	//������ PW ����
			Wrtie_String(file_gate, AE->PW);
			Write_Operator(file_gate, END_OP, (char)NULL);

			Write_Operator(file_gate, START_OP, INPUT_ACCOUNT_CURRENT_UPDATE);	//������ ������Ʈ �ð� ����
			if (!strcmp(AE->Update_Time, NULL_MESSAGE))	//������Ʈ �ð� �ڵ����� ����� �����ϰ� �������� �� �κ��� �ʿ��������.
				Write_Operator(file_gate, EMPTY_OP, (char)NULL);
			else
			{
				Wrtie_String(file_gate, AE->Update_Time);
				Write_Operator(file_gate, END_OP, (char)NULL);
			}

			Write_Operator(file_gate, START_OP, INPUT_ACCOUNT_MEMO);	//������ ���� �޸� ����
			if (!strcmp(AE->Memo, NULL_MESSAGE))	//�޸� ������ NULL_MESSAGE�� �����ϰ�
				Write_Operator(file_gate, EMPTY_OP, (char)NULL);	//��ũ�η� ���ǵ� EMPTY_OP�� �����Ѵ�.
			else
			{
				Wrtie_String(file_gate, AE->Memo);
				Write_Operator(file_gate, END_OP, (char)NULL);
			}
			AE = AE->next;
		}
		Write_Operator(file_gate, START_OP, END_INPUT_SITE);
		SA = SA->next;
	}
	Write_Operator(file_gate, START_OP, END_PROGRAM);
#if ACTIVE_ENCODING
#if GENERATE_JUNK_BYTE
	Write_Random_Byte(file_gate, LOOK_NORMALLY_CHAR,	MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, ALPHABET_ONLY,				MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, LOOK_NORMALLY_CHAR,	MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, ALPHABET_ONLY,				MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, DIGIT_ONLY,						MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
	Write_Random_Byte(file_gate, LOOK_NORMALLY_CHAR,	MIN_OF_CREATE_JUNK_BYTES, MAX_OF_CREATE_JUNK_BYTES);
#endif
#endif
	fclose(file_gate);
	printf("\nexport() ���� : ���� [./%s]\n", EXPORT_FILE_NAME);
	Unload_History();
}
void Write_Operator(FILE * file_gate, char Op_Symbol, char Operator_Number)
{
	char temp_store_Op_Symbol = Op_Symbol;
	Encoding_Byte(&Op_Symbol);
	fwrite(&Op_Symbol, ONE_BYTE, ONCE, file_gate);
	if (temp_store_Op_Symbol == START_OP) //���� START_OP��� �ڿ� �� ��ȣ�� ���� ���ڰ� ���� ���̹Ƿ�
	{
		Encoding_Byte(&Operator_Number);
		fwrite(&Operator_Number, ONE_BYTE, ONCE, file_gate);
	}
}
void Write_Random_Byte(FILE * file_gate, int how_type_random, int min_time, int max_time)
{
	char random_byte ;
	int iteration_of_times = RANDOM(min_time, max_time);
	while (iteration_of_times--)
	{
		switch (how_type_random)
		{
			case ENTIRE_TYPE:	//�������� ���� ����.
				random_byte = rand() % 256;
				break;
			case DIGIT_ONLY:
				random_byte = RANDOM('0','9');
				break;
			case LOOK_NORMALLY_CHAR:
				random_byte = RANDOM('!', '~');
				break;
			case ALPHABET_ONLY:
				random_byte = RANDOM('A', 'z');
				if (random_byte > 'Z'&& random_byte < 'a')
					continue;
				break;
		}
		if (random_byte == START_OP		||
			random_byte == END_OP			||
			random_byte == EMPTY_OP		||
			random_byte == ASCII_BELL	)
			continue;
		Encoding_Byte(&random_byte);
		if ((iteration_of_times - rand())%64 == 0)
		{
			MAKE_BUFFER(time);
			What_Time_Is_It(time);
			Wrtie_String(file_gate, time);
		}
		fwrite(&random_byte, ONE_BYTE, ONCE, file_gate);
	}
}
void Wrtie_String(FILE * file_gate, char str[COMMON_LENGTH])
{
	int i = 0;
	char byte;
	while (1)
	{
		byte = str[i++];
		if (byte == (char)NULL)
			return;
		else
		{
			Encoding_Byte(&byte);
			fwrite(&byte, ONE_BYTE, ONCE, file_gate);
		}
	}
}
void Encoding_Byte(char * byte)
{
#if EXPORT_DEBUG
#if SHOW_ENCODING_PROCESS
	SET_COLOR(PURPLE);
	printf("%c", (*byte));
	SET_COLOR_DEFAULT;
#endif
#endif
#if ACTIVE_ENCODING
	if ((*byte) != (char)NULL)
		(*byte) ^= START_OP;
#endif
}