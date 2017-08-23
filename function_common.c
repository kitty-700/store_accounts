#include "all_included.h"

extern History * clue;

int Is_Buffer_Contain_Operator_Symbol(const char buffer[COMMON_LENGTH])
{	//�ý����� �����ϴ� ���ڰ� �����ִ��� Ȯ���Ѵ�.
	for (int i = 0; i < COMMON_LENGTH; i++)
		if (buffer[i] == START_OP || buffer[i] == END_OP || buffer[i] == EMPTY_OP)
			return TRUE;
		else if (buffer[i] == (char)NULL)
			return FALSE;
	return FALSE;
}
void What_Time_Is_It(char buffer_to_store_time[UPDATE_TIME_SIZE])
{	//�迭�� �ð� �����ϴ� �Լ��� ��
	time_t timer = time(NULL);
	struct tm t;
	localtime_s(&t, &timer);
	sprintf_s(buffer_to_store_time, UPDATE_TIME_SIZE, "%4d-%02d-%02d %02d:%02d:%02d",
		t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}
int Is_Start_with_Digit(const char buffer[COMMON_LENGTH])
{
	if (_NOT_A_NUMBER(buffer[0]))
		return FALSE;
	else
		return TRUE;
}
void Show_Accounts_Relevant_Site_Number(DB * root, char buffer[COMMON_LENGTH])
{
	int select = Input_String_Then_Return_Integer(buffer);
	if (select == UNIVERSAL_ZERO)
		Show_SA(root, SITE_ONLY);
	else if (select > 0 && select <= root->how_many_sites)
	{
		Site_Account * SA = Find_SA_Through_Number(root, select);
		if (SA == NOTHING_POINTER)
			BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(������ ����));
		SET_COLOR(SITE_BASIC_COLOR);
		printf("[%03d] %s    ( %d ���� ���� ��)\n", select, SA->Site_Name, SA->how_many_accounts);
		SET_COLOR_DEFAULT;
		Show_AE(SA);
	}
	else
		;// printf("�ش� ��ȣ�� ����Ʈ�� �������� ����.\n");
	return;
}
void Login()
{
	Delay_n_Second_and_Print_Dots(IMPORT_DELAY_SEC);
	printf("�ε��ϱ⿡ ������ ������ ã�� �� ����.\n");
	printf("���� Ű�� ���� �����մϴ�.\n");
	if ((char)_getch() != PASS_CHAR1)
		exit(0);
	else
#if USE_PASSWORD_IN_LOGIN
	{
		MAKE_BUFFER(password_input);
		printf("Password > ");
		SET_COLOR(ORDER_COLOR);
		gets_s(password_input, ORDER_LENGTH);
		SET_COLOR_DEFAULT;
		if (strcmp(password_input, THEN_PASSWORD))
			exit(0);
		else
			;
	}
#else
	{
		;
	}
#endif
}
int Ask_Continue(const char buffer[COMMON_LENGTH])
{//��뿹�� if (Continue("�����Ͻðڽ��ϱ� ? y / else") == FALSE)
	printf("%s y / else\n", buffer);
	if ((char)_getch() == 'y')
		return TRUE;
	else
		return FALSE;
}
void Delay_n_Second_and_Print_Dots(int n_sec)
{
	n_sec *= 1000;
	int the_number_of_dots = 5;
	if (the_number_of_dots == 0)
		return;
	n_sec /= the_number_of_dots;
	while (the_number_of_dots--)
	{
		Sleep(n_sec);
		printf(" . ");
	}
}
int Input_String_Then_Return_Integer(const char input_string[COMMON_LENGTH])
{
	int result = 0;
	MAKE_BUFFER(buffer);
	if (input_string[0] == (char)NULL)
		return NO_INPUT;
	int buffer_length = Check_String_and_Return_Filtered_Buffer(input_string, buffer);
	if (buffer_length == (int)NOT_A_NUMBER)
		return NOT_A_NUMBER;
	else if (buffer_length == (int)INTENDED_ZERO)
		return UNIVERSAL_ZERO;
	else if (buffer_length == 0)
		return NO_INPUT;
	else
	{
		int i = 0;
		while (i < buffer_length)
		{
			int each_number = buffer[i] - '0';
			result += power(10, buffer_length - i - 1) * each_number;
			//printf("each : %d , result : %d\n", each_number, result); //�Լ� ���� �� debug
			i++;
		}
	}
	return result;
}
int Check_String_and_Return_Filtered_Buffer(const char input_string[COMMON_LENGTH], char buffer[COMMON_LENGTH])
{	//input_string ���� ������� 0�� ������ ���� �Է¹��� buffer�� �ٽ� �����ϰ� buffer�� ���̸� ��ȯ
	int buffer_index = 0;
	int buffer_length = 0;
	int is_first_word = TRUE;
	char input_char;
	if (input_string[0] == '0' && input_string[1] == (char)NULL)
		return INTENDED_ZERO;
	for (int input_string_index = 0; input_string_index < COMMON_LENGTH; input_string_index++)
	{
		input_char = input_string[input_string_index];
		if (input_char == (int)NULL)
			break;
		if (buffer_length >= INT_LIMIT_LENGTH)
			//������ int ���̴ϱ� 10�ڸ������ۿ� ��� �� ��. (�׸����� 10��° �ڸ��� �����̴ϱ� 9��°������ �������)
			break;
		if (input_char == '0' && is_first_word == TRUE)	
			//������ ù��° �ڸ��� 0�̸� ����.
			continue;	
		if (input_char == ' ')
			//���� ���̻��̿� ������ ���ԵǾ��ִٸ� ����.
			continue;
		if (_NOT_A_NUMBER(input_char) == TRUE)	
			//�Էµ� ���� ���ڰ� �ƴϸ� ���� ��ȯ.
			return NOT_A_NUMBER;
		else
		{
			buffer[buffer_index++] = input_char;
			buffer_length++;
			is_first_word = FALSE;
		}
	}
	return buffer_length;
}
int power(int a, int num)
{
	if (num == 0)
		return 1;
	return a * power(a, num - 1);
}
void test_anyway_function()
{
	int result = 20;
	for (int i = 0; i < 21999999; i++)
		result += i;
}
int is_digit_char(char byte)
{
	if (byte >= '0' && byte <= '9')
		return YES;
	else
		return NO;
}
void Unload_DB(DB * root)
{
	if (root->first_Site != NULL)
	{
		Site_Account * SA_del = root->first_Site;
		Site_Account * SA_del_next = SA_del->next;
		root->first_Site = NULL;

		while (SA_del != NULL)
		{
			Account_Element * AE_del = SA_del->head;
			if (AE_del != NULL)
			{
				Account_Element * AE_del_next = AE_del->next;
				while (AE_del != NULL)
				{
					//printf("���� ID : %s , unload.\n", AE_del->ID);
					free(AE_del);
					AE_del = AE_del_next;
					if (AE_del != NULL)
						AE_del_next = AE_del->next;
				}
			}
			//printf("����Ʈ %s , unload.\n", SA_del->Site_Name);
			free(SA_del);
			root->how_many_sites--;
			SA_del = SA_del_next;
			if (SA_del != NULL)
				SA_del_next = SA_del->next;
		}
	}
	//printf("DB ���� �����͸� ���� ��ü�߽��ϴ�.\n");
}
void Unload_History()
{
	if (clue->first != NULL)
	{
		Change_Something * CS_del = clue->first;
		Change_Something * CS_del_next = CS_del->next;
		clue->first = clue->last = NULL;
		while (CS_del != NULL)
		{
			free(CS_del);
			clue->how_many_changes--;
			CS_del = CS_del_next;
			if (CS_del != NULL)
				CS_del_next = CS_del->next;
		}
	}
	//printf("���� ����� ���� ��ü�߽��ϴ�.\n");
	//printf("���� ������ ������ ������ �ִٸ� ������ Ȯ���� �� ������ ���� �� ���� �ٶ��ϴ�.\n");
}
void Reload(DB * root, int * is_loaded)
{	//���� ����� ��
	int is_something_changes = History_Show();
	if (is_something_changes == FALSE)
		printf("�׷����� ");
	if (Ask_Continue("�ٽ� �ε��Ͻðڽ��ϱ�?") == FALSE)
		return;
	Unload_DB(root);
	Unload_History();
	*is_loaded = FALSE;
	system("cls");
}
void Quit_Program(DB * root)
{
	if (clue->how_many_changes != 0)
	{
		History_Show();
		if (Ask_Continue("���� ����� �ִµ��� �����Ͻðڽ��ϱ�?") == FALSE)
		{
			printf("��� ���� ��ɾ�� \"save\" �Դϴ�.\n");
			return;
		}
	}
	Unload_DB(root);
	Unload_History();
	exit(0);
}

Order_Type Convert_Orderset_to_Interger(char Order[COMMON_LENGTH])
{	//���ǻ� �߿��� ��ɾ ���� ��ġ�ߴ� Operation_System()�Լ������ʹ� �޸�
	//strcmp ������带 ���̱� ���ؼ� ���� ���� ��ɾ ���� ��ġ�Ѵ�.
	if (Order[0] == (char)NULL)
		return no_input;

	if (ORDER_IS_("ls") ||
		ORDER_IS_("sl") ||
		ORDER_IS_("list show") ||
		ORDER_IS_("site") || 
		ORDER_IS_("s") || 
		ORDER_IS_("show"))
		return show_site_list;

	if (Is_Start_with_Digit(Order))
		return show_account_through_number;

	if (ORDER_IS_("add") || 
		ORDER_IS_("a"))
		return add_something;

	if (ORDER_IS_("update") ||
		ORDER_IS_("ud") ||
		ORDER_IS_("u"))
		return update_something;

	if (ORDER_IS_("delete") ||
		ORDER_IS_("remove") ||
		ORDER_IS_("del") ||
		ORDER_IS_("de") ||
		ORDER_IS_("rm") ||
		ORDER_IS_("d"))
		return delete_something;

	if (ORDER_IS_("cls") ||
		ORDER_IS_("clear") ||
		ORDER_IS_("c"))
		return clear_display;

	if (ORDER_IS_("swap") ||
		ORDER_IS_("w"))
		return swap_site_order;

	if (ORDER_IS_("nothing") ||
		ORDER_IS_("n"))
		return do_nothing;

	if (ORDER_IS_("export") ||
		ORDER_IS_("save") ||
		ORDER_IS_("\"save\"") ||
		ORDER_IS_("x"))
		return export_data;

	if (ORDER_IS_("exit") ||
		ORDER_IS_("close") ||
		ORDER_IS_("quit") ||
		ORDER_IS_("q"))
		return quite_program;

	if (ORDER_IS_("help") ||
		ORDER_IS_("how") ||
		ORDER_IS_("h") ||
		ORDER_IS_("?"))
		return help;

	if (ORDER_IS_("reload") ||
		ORDER_IS_("r"))
		return re_import;

	if (ORDER_IS_("history") || 
		ORDER_IS_("log") ||
		ORDER_IS_("l"))
		return show_change_history;

	if (ORDER_IS_("undb"))
		return unset_DB;

	if (ORDER_IS_("unlog"))
		return unset_history;

	if (ORDER_IS_("ll") ||
		ORDER_IS_("account") ||
		ORDER_IS_("detail"))
		return show_account_list;

	return undefined_order;
}