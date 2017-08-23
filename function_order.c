#include "all_included.h"

static History history = { NULL,NULL,0 };
History * clue = &history;

void Add(DB * root)
{
	system("cls");
	int select_in_first_page;	///����Ʈ�� ���� ���� ������ ������ ����Ʈ�� ������ �߰��� ������ ������.
	select_in_first_page = Select_SA_Number(root,
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"������ �߰��ϰ��� �ϴ� ����Ʈ ��ȣ Ȥ�� '0'�� �Է��ϼ���.",
										/*0�� ���ý�*/	"���ο� ����Ʈ ���.",
		SHOW_LIST);
	Site_Account * new_SA = NULL;
	Account_Element * new_AE = NULL;
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	switch (select_in_first_page)
	{
		case COMMON_CANCEL_REASON(�߰�);
		case MAKE_NEW_SITE:
			new_SA = Fill_the_SA_Form();
			if (new_SA == (Site_Account *)NO_INPUT)
				BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(�߰�));
			if (new_SA == (Site_Account *)SYSTEM_CHAR_INPUT)
				BEFORE_RETURN_PRINT_(MESSAGE_SYSTEM_INVAIDING_INPUT(�߰�));
			if (new_SA == (Site_Account *)NOTHING_POINTER)
				BEFORE_RETURN_PRINT_(MESSAGE_UNKNOWN_ERROR(�߰�));
			/*���Լ� ������*///-> ����Ʈ �߰� ����
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ����Ʈ �߰�", root->how_many_sites + 1, new_SA->Site_Name);
			sprintf_s(history_record_2, COMMON_LENGTH, "");
			Attach_SA_to_the_DB(new_SA, root);
			History_Add(HISTORY_ADD, history_record_1, history_record_2);
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(����Ʈ �߰�));
			/*���Լ� ������*/
		default: //�̹� �����ϴ� ����Ʈ�� �����ߴٸ�
			new_SA = Find_SA_Through_Number(root, select_in_first_page);
			if (new_SA == NOTHING_POINTER)
				BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(�߰�));
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ����Ʈ�� ���� �߰�", select_in_first_page, new_SA->Site_Name);

	}
	__________PRINT_DEVIDE_LINE__________;
	new_AE = Fill_the_AE_Form();
	if (new_AE == (Account_Element *)NO_INPUT)
		BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(�߰�));
	if (new_AE == (Account_Element *)SYSTEM_CHAR_INPUT)
		BEFORE_RETURN_PRINT_(MESSAGE_SYSTEM_INVAIDING_INPUT(�߰�));
	if (new_AE == (Account_Element *)NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_UNKNOWN_ERROR(�߰�));
	/*���Լ� ������*///-> ���� �߰� ����
	Attach_AE_to_the_SA(new_AE, new_SA);
	sprintf_s(history_record_2, COMMON_LENGTH, "\t[%03d]\tID : %s\n\t\t\tPW : %s", FIRST, new_AE->ID, new_AE->PW);
	//�� ���⼭ ���۰� ���� Ȯ���� 2������ �ϴ� �����ϴ� ������
	History_Add(HISTORY_ADD, history_record_1, history_record_2);
	BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(���� �߰�));
	/*���Լ� ������*/
}
void Update(DB * root)
{
	if (DB_EMPTY)
		BEFORE_RETURN_PRINT_("DB�� ��������Ƿ� ������Ʈ ���.\n"); 
	system("cls");
	int select_in_first_page;		///������Ʈ�� ����Ʈ�� ������.
	int select_in_second_page;	///����Ʈ �̸��� ������Ʈ �� ������ ����Ʈ ���� ������ ������Ʈ�� ������ ������.
	int select_in_third_page;		///����Ʈ �� ������ ��� ��Ҹ� ������Ʈ�� ������ ������.
	MAKE_BUFFER(string_to_be_replaced);
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	select_in_first_page = Select_SA_Number(root,
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"������Ʈ �� ����Ʈ ��ȣ Ȥ�� '0'�� �Է��ϼ���.",
										/*0�� ���ý�*/	"������Ʈ ���.",
		SHOW_LIST);
	switch (select_in_first_page)
	{
		case COMMON_CANCEL_REASON(������Ʈ);
		case CANCEL_UPDATE:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(������Ʈ));
	}
	Site_Account * to_be_updated_SA = Find_SA_Through_Number(root, select_in_first_page);
	if (to_be_updated_SA == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(������Ʈ));
	system("cls");
	SET_COLOR(SITE_BASIC_COLOR);
	printf("���õ� > [%03d] %s\n", select_in_first_page, to_be_updated_SA->Site_Name);
	SET_COLOR_DEFAULT;
	__________PRINT_DEVIDE_LINE__________;
	select_in_second_page = Select_AE_Number(to_be_updated_SA,
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"������Ʈ �� ���� ��ȣ Ȥ�� '0'��  �Է��ϼ���.",
										/*0�� ���ý�*/	"������ ����Ʈ �̸� ����",
		SHOW_LIST);
	switch (select_in_second_page)
	{
		case COMMON_CANCEL_REASON(������Ʈ);
		case CHANGE_SITE_NAME:
			//UNIVERSAL_ZERO == 0
			printf("\tSite Name : %s -> ? ", to_be_updated_SA->Site_Name);
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d]\t\" %s \" ����Ʈ�� �̸���", select_in_first_page, to_be_updated_SA->Site_Name);
			SET_COLOR(ORDER_COLOR);
			gets_s(string_to_be_replaced, SITE_NAME_LENGTH);
			SET_COLOR_DEFAULT;
			COMMON_STRING_INPUT_CANCEL_REASON(string_to_be_replaced, ������Ʈ);
			strcpy_s(to_be_updated_SA->Site_Name, SITE_NAME_LENGTH, string_to_be_replaced);
			sprintf_s(history_record_2, COMMON_LENGTH, "\t\" %s \" �� ������Ʈ�߽��ϴ�.", to_be_updated_SA->Site_Name);
			/*���Լ� ������*///-> ����Ʈ �̸� ������Ʈ ����
			History_Add(HISTORY_UPDATE, history_record_1, history_record_2);
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(������Ʈ));
			/*���Լ� ������*/
	}
	Account_Element * update_AE = Find_AE_Through_Number(to_be_updated_SA, select_in_second_page);
	if (update_AE == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(������Ʈ));
	system("cls"); 
	SET_COLOR(SITE_BASIC_COLOR);
	printf("���õ� > [%03d] %s\n", select_in_first_page, to_be_updated_SA->Site_Name);
	SET_COLOR_DEFAULT;
	SET_COLOR(ACCOUNT_BASIC_COLOR);
	printf("���õ� > [%03d]\n\tID :%s\n", select_in_second_page, update_AE->ID);
	SET_COLOR_DEFAULT;
	__________PRINT_DEVIDE_LINE__________;
	select_in_third_page = Select_AE_Attribute(
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"������Ʈ �� �׸��� ��ȣ Ȥ�� '0'�� �Է��ϼ���.",
										/*0�� ���ý�*/	"������Ʈ �۾� ���.");
	switch (select_in_third_page)
	{
		case COMMON_CANCEL_REASON(������Ʈ);
		case CANCEL_UPDATE:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(������Ʈ));
	}
	switch (select_in_third_page)
	{
	case 1: //ID ����
		printf("\tID : %s -> ? ", update_AE->ID);
		break;
	case 2: //PW ����
		printf("\tPW : %s -> ? ", update_AE->PW);
		break;
	case 3: //�޸� ����
		printf("\tMEMO : %s -> ? ", update_AE->Memo);
		break;
	default: //���� (���� �� ����.)
		BEFORE_RETURN_PRINT_("����!!\n");
	}
	SET_COLOR(ORDER_COLOR);
	gets_s(string_to_be_replaced, COMMON_LENGTH);
	SET_COLOR_DEFAULT;
	COMMON_STRING_INPUT_CANCEL_REASON(string_to_be_replaced, ������Ʈ);
	switch (select_in_third_page)
	{
	case 1: //ID ����
		sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ����Ʈ��\n\t\t[%03d] ID : %s �� ID ��\n\t\t\t\" %s \" ����",
			select_in_first_page, to_be_updated_SA->Site_Name, select_in_second_page, update_AE->ID, update_AE->ID);
		strcpy_s(update_AE->ID, ID_LENGTH, string_to_be_replaced); 
		break;
	case 2: //PW ����
		sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ����Ʈ��\n\t\t[%03d] ID : %s �� PW ��\n\t\t\t\" %s \" ����",
			select_in_first_page, to_be_updated_SA->Site_Name, select_in_second_page, update_AE->ID, update_AE->PW);
		strcpy_s(update_AE->PW, PASSWORD_LENGTH, string_to_be_replaced); 
		break;
	case 3: //�޸� ����
		sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ����Ʈ��\n\t\t[%03d] ID : %s �� Memo ��\n\t\t\t\" %s \" ����",
			select_in_first_page, to_be_updated_SA->Site_Name, select_in_second_page, update_AE->ID, update_AE->Memo);
		strcpy_s(update_AE->Memo, MEMO_LENGTH, string_to_be_replaced); 
		break;
	}
	sprintf_s(history_record_2, COMMON_LENGTH, "\t\t\" %s \" �� ����.", string_to_be_replaced);
	/*���Լ� ������*///-> ���� ���� ������Ʈ ����
	What_Time_Is_It(string_to_be_replaced);
	strcpy_s(update_AE->Update_Time, COMMON_LENGTH, string_to_be_replaced);
	History_Add(HISTORY_UPDATE, history_record_1, history_record_2);
	BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(������Ʈ));
	/*���Լ� ������*/
}

void Delete(DB * root)
{
	if (DB_EMPTY)
		BEFORE_RETURN_PRINT_("DB�� ��������Ƿ� ���� ���.\n");
	//DB�� �ڷᰡ �����ϴ��� �˻�///////////////////////////////////////////
	system("cls");
	int select_in_first_page;		///� ����Ʈ ������ ������ ������ ������.
	int select_in_second_page;	///����Ʈ ��ü�� ������ ������ ����Ʈ ���� � ���� �ϳ��� ������ ������ ������.
	select_in_first_page = Select_SA_Number(root,
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"������ ����Ʈ ��ȣ Ȥ�� '0'�� �Է��ϼ���.",
										/*0�� ���ý�*/	"���� ���.",
		SHOW_LIST);
	switch (select_in_first_page)
	{
		case COMMON_CANCEL_REASON(����);
		case CANCEL_DELETE:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(����));
	}
	Site_Account * delete_SA = Find_SA_Through_Number(root, select_in_first_page);
	if (delete_SA == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(����));
	system("cls");
	SET_COLOR(SITE_BASIC_COLOR);
	printf("���õ� > [%03d] %s\n", select_in_first_page, delete_SA->Site_Name);
	SET_COLOR_DEFAULT;
	__________PRINT_DEVIDE_LINE__________;
	select_in_second_page = Select_AE_Number(delete_SA,
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"������ �� ���� ��ȣ Ȥ�� '0'��  �Է��ϼ���.",
										/*0�� ���ý�*/	"������ ����Ʈ ����.",
		SHOW_LIST);
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	switch (select_in_second_page)
	{
		case COMMON_CANCEL_REASON(����);
		case DELETE_SITE:
		{
			if (Ask_Continue("�����Ͻðڽ��ϱ� ?") == FALSE)
				BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(����));
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ����Ʈ�� �����߽��ϴ�.", select_in_first_page, delete_SA->Site_Name);
			sprintf_s(history_record_2, COMMON_LENGTH, "");
			if (Delete_SA_From_DB(delete_SA, root) == FAIL)
				BEFORE_RETURN_PRINT_(MESSAGE_FAIL(����));
			/*���Լ� ������*///-> ����Ʈ ���� ����
			History_Add(HISTORY_DELETE, history_record_1, history_record_2);
			root->how_many_sites--;
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(����));
			/*���Լ� ������*/
		}
		default: //0���� �ƴ϶� ���� ��ȣ�� �������� ���
		{
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ����Ʈ��", select_in_first_page, delete_SA->Site_Name);
			Account_Element * delete_AE = Find_AE_Through_Number(delete_SA, select_in_second_page);
			if (delete_AE == NOTHING_POINTER)
				BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(����));
			system("cls");
			SET_COLOR(SITE_BASIC_COLOR);
			printf("���õ� > [%03d] %s\n", select_in_first_page, delete_SA->Site_Name);
			SET_COLOR_DEFAULT;
			SET_COLOR(ACCOUNT_BASIC_COLOR);
			printf("���õ� > [%03d]\n\tID :%s\n", select_in_second_page, delete_AE->ID);
			SET_COLOR_DEFAULT;
			printf("\tPW :%s\n", delete_AE->PW);
			printf("\tUD :%s\n", delete_AE->Update_Time);
			printf("\tMM :%s\n", delete_AE->Memo);
			__________PRINT_DEVIDE_LINE__________;
			if (Ask_Continue("�����Ͻðڽ��ϱ�?") == FALSE)
				BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(����));
			sprintf_s(history_record_2, COMMON_LENGTH, "\t[%03d] ID : %s ������ �����߽��ϴ�.", select_in_second_page, delete_AE->ID);
			if (Delete_AE_From_SA(delete_AE, delete_SA) == FAIL)
				BEFORE_RETURN_PRINT_(MESSAGE_FAIL(����)); 
			/*���Լ� ������*///-> ���� ���� ����
			History_Add(HISTORY_DELETE, history_record_1, history_record_2);
			delete_SA->how_many_accounts--;
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(����));
			/*���Լ� ������*/
		}
	}
}
void Swap_Site_Order(DB * root)
{
	if (DB_EMPTY)
		BEFORE_RETURN_PRINT_("DB�� ��������Ƿ� ���� ���.\n");
	//DB�� �ڷᰡ �����ϴ��� �˻�///////////////////////////////////////////
	system("cls");
	int select_1, select_2;
	Site_Account * SA_1 = NULL;
	Site_Account * SA_2 = NULL;
	select_1 = Select_SA_Number(root,
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"��ȯ�� ����Ʈ�� ��ȣ Ȥ�� '0'�� �Է��ϼ���",
										/*0�� ���ý�*/	"��ȯ ���",
		SHOW_LIST);
	switch (select_1)
	{
		case COMMON_CANCEL_REASON(��ȯ);
		case CANCEL_SWAP:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(��ȯ));
	}
	select_2 = Select_SA_Number(root,
		/*�Է¹ޱ� ���� ����� ���� �޼���*/	"��ȯ�� ����Ʈ�� ��ȣ Ȥ�� '0'�� �Է��ϼ���",
										/*0�� ���ý�*/	"��ȯ ���",
		DONT_SHOW_LIST);
	switch (select_2)
	{
		case COMMON_CANCEL_REASON(��ȯ);
		case CANCEL_SWAP:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(��ȯ));
	}
	if (select_1 == select_2)
		BEFORE_RETURN_PRINT_("������ ����Ʈ�Դϴ�.\n");
	if (select_1 > select_2) //select_1�� �� ���� ��ȣ���� �Ѵ�. �׷��� ���� ����.
	{	//swap select_1 and select_2
		int temp_select = select_1;
		select_1 = select_2;
		select_2 = temp_select;
	}
	SA_1 = Find_SA_Through_Number(root, select_1);
	if (SA_1 == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(��ȯ));
	SA_2 = Find_SA_Through_Number(root, select_2);
	if (SA_2 == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(��ȯ));
	{	//�� �����͸� �ٲٴ� ��ƾ�� �� �߰�ȣ ����
		Site_Account * previous_of_SA_1 = root->first_Site;
		Site_Account * previous_of_SA_2 = SA_1;	///������ SA_2�� �ּ��� swap_SA_1 ���� ��ȣ�� ���� ���̱� ����
		while (previous_of_SA_2->next != SA_2)
			previous_of_SA_2 = previous_of_SA_2->next;
		if (SA_1 != root->first_Site)	///swap_SA_1 �� �� ù��° SA�ε� �� ���� SA ��� ������ ������ �� �Ǵϱ�.
		{
			while (previous_of_SA_1->next != SA_1)
				previous_of_SA_1 = previous_of_SA_1->next;
			previous_of_SA_1->next = SA_2;									///-> �� ������ previous_of_SA_1�� �ۿ��� �� �ִ�.
		}
		else			//SA_1�� DB ���� ù��° SA���?
			root->first_Site = SA_2;
		if (SA_1 == previous_of_SA_2)	//SA_2�� �ٷ� ���� SA_1�� ���
		{
			SA_1->next = SA_2->next;
			SA_2->next = SA_1;
		}
		else if (SA_1 != previous_of_SA_2)	//SA_2�� �ٷ� ���� SA_1�� �ƴ� ���
		{
			Site_Account * SA_temp = SA_1->next;
			SA_1->next = SA_2->next;
			SA_2->next = SA_temp;
			previous_of_SA_2->next = SA_1;
		}
	}
	//�̰� ��� �����ߴ��� �������� �� ��
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	SET_COLOR(SITE_BASIC_COLOR);
	printf("[%03d] %s ", select_1, SA_1->Site_Name);
	SET_COLOR_DEFAULT;
	printf("��(/��) \n");
	SET_COLOR(SITE_BASIC_COLOR);
	printf("[%03d] %s ", select_2, SA_2->Site_Name);
	SET_COLOR_DEFAULT;
	printf("�� ��ġ�� ��ȯ�߽��ϴ�.\n");
	sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s ��(/��)", select_1, SA_1->Site_Name);
	sprintf_s(history_record_2, COMMON_LENGTH, "[%03d] %s �� ��ġ�� ��ȯ�߽��ϴ�.", select_2, SA_2->Site_Name);

	History_Add(HISTORY_SWAP, history_record_1, history_record_2);
}
void History_Add(int order_number, const char str_1[COMMON_LENGTH], const char str_2[COMMON_LENGTH])
{	//1~2���� ���ڿ��� CS ����ü�� �ܼ��� ���̴� ����
	Change_Something * temp_CS = (Change_Something*)malloc(sizeof(Change_Something));
	temp_CS->change_operator = order_number;
	temp_CS->next = NULL;

	if (STRING_INPUT(str_1))
		strcpy_s(temp_CS->change_from, COMMON_LENGTH, str_1);
	else
		strcpy_s(temp_CS->change_from, COMMON_LENGTH, "");
	if (STRING_INPUT(str_2))
		strcpy_s(temp_CS->change_to, COMMON_LENGTH, str_2);
	else
		strcpy_s(temp_CS->change_to, COMMON_LENGTH, "");
	////////////////////////////////////////////////////////////
	if (HISTORY_EMPTY)
		clue->first = clue->last = temp_CS;
	else
	{
		clue->last->next = temp_CS;
		clue->last = temp_CS;
	}
	////////////////////////////////////////////////////////////
	clue->how_many_changes++;
	/* �Լ� ���
	MAKE_BUFFER(buffer_1);
	MAKE_BUFFER(buffer_2);
	sprintf_s(buffer_1, COMMON_LENGTH, "[%03d] %s ��(/��)", select_1, SA_1->Site_Name);
	sprintf_s(buffer_2, COMMON_LENGTH, "[%03d] %s �� ��ġ�� ��ȯ�߽��ϴ�.", select_2, SA_2->Site_Name);
	History_Add(HISTORY_SWAP, buffer_1, buffer_2);
	/*���Լ� ������
	/*���Լ� ������*/
}
int History_Show()
{
	if (HISTORY_EMPTY)
		BEFORE_RETURN_INTEGER_PRINT_("���� ���� �����ϴ�.\n", FALSE);
	Change_Something * temp_CS = clue->first;
	int count_each_change = 1;
	SET_COLOR(HISTORY_COLOR);
	while (temp_CS != NULL)
	{
		printf("[%03d] ", count_each_change++);
		switch (temp_CS->change_operator)
		{
		case HISTORY_ADD:
			printf("ADD\n");
			break;
		case HISTORY_DELETE:
			printf("DELETE\n");
			break;
		case HISTORY_UPDATE:
			printf("UPDATE\n");
			break;
		case HISTORY_SWAP:
			printf("SWAP\n");
			break;
		case HISTORY_NOTHING:
			printf("NOTHING\n");
			break;
		default:
			printf("����\n");
			break;
		}
		if (STRING_INPUT(temp_CS->change_from))
			printf("\t%s\n", temp_CS->change_from);
		if (STRING_INPUT(temp_CS->change_to))
			printf("\t%s\n", temp_CS->change_to);
		temp_CS = temp_CS->next;
	}
	printf("\n�� %d ���� ������ ���� ����� �־����ϴ�.\n", clue->how_many_changes);
	SET_COLOR_DEFAULT;
	return TRUE;
}

int How_To_Use_Operations()
{	//Help
	__________PRINT_DEVIDE_LINE__________;
	printf("%s  / %s ����!\n", __DATE__, __TIME__);
#if SHOW_SOURCE
	printf("kitty ����, ������ knukit@naver.com ����\n");
#endif
	printf("%s\n", HELP_MESSAGE);
	__________PRINT_DEVIDE_LINE__________;
	printf("%-10s (s)\t:����Ʈ ����\n", "ls");
	printf("%-10s (a)\t:����Ʈ Ȥ�� ���� �߰��ϱ�\n", "add");
	printf("%-10s (d)\t:����Ʈ Ȥ�� ���� �����ϱ�\n", "del");
	printf("%-10s (u)\t:����Ʈ Ȥ�� ���� �����ϱ�\n", "upate");
	printf("%-10s (w)\t:����Ʈ ���� ����\n", "swap");
	printf("%-10s (l)\t:���� ���� ���\n", "history");
	printf("%-10s (c)\t:ȭ���� �����ϰ� �����\n", "cls");
	printf("%-10s (x)\t:��� ������ ���Ͽ� ����\n", "save");
	printf("%-10s (q)\t:���α׷� ����\n", "exit");

	printf("������ ��Ȳ���� �ƹ� �Էµ� �� �ϰ� ���͸� ������ �۾���Ҹ� �ǹ��մϴ�.\n");
	printf("�۾��� ����ϴ� ���� �̻��� �����͸� ����ִ� �ͺ��ٴ� ���� ���Դϴ�.\n");
	return 0;
}
