#include "all_included.h"

//Show....() -> ���� ���
void Show_SA(const DB * root, const int present_what_section)
{
	int count = 1;
	if (root->first_Site == NULL)
		printf("���� ��ϵ� ����Ʈ�� �ϳ��� �����ϴ�.\n");
	else
	{
		Site_Account * each_site = root->first_Site;
		while (each_site != NULL)
		{
			SET_COLOR(SITE_BASIC_COLOR);
			printf("[%03d] %s    ( %d ���� ���� ��)\n", count++, each_site->Site_Name, each_site->how_many_accounts);
			SET_COLOR_DEFAULT;
			if (present_what_section == SITE_AND_ACCOUNTS)
				Show_AE(each_site);
			else if (present_what_section == SITE_ONLY)
				DO_NOTHING;
			each_site = each_site->next;
		}
	}
}
void Show_AE(const Site_Account * SA)	// ls
{
	int count = 1;
	if (SA->head == NULL)
		printf("���� ����Ʈ %s�� ��ϵ� ������ �ϳ��� �����ϴ�.\n", SA->Site_Name);
	else
	{
		Account_Element * each_account = SA->head;
		while (each_account != NULL)
		{
			SET_COLOR(ACCOUNT_BASIC_COLOR);
			printf("[%03d]\n", count++);
			printf("    ID : %s\n", each_account->ID);
			SET_COLOR_DEFAULT;
			printf("    PW : %s\n", each_account->PW);
			printf("    UD : %s\n", each_account->Update_Time);
			printf("    MM : %s\n", each_account->Memo);
			each_account = each_account->next;
		}
	}
}
//Show....()

/*Select....() -> ������ ���� ��ȣ�� ��ȯ. 
���⼭�� buffer�� �Է¹ޱ� ���� �ϰ� ���� ��, 
active_zero_message�� 0���� �������� ����� �޼���
*/
int Select_SA_Number(DB * root, char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH], int is_show_SA)
{	//��ȯ�� �� �˻��ؾ��� ���
	//1. �ƹ� �Է¾��� ���͸� ĥ ���
	//2. ���ڸ��� ���� �Է����� ���
	//3. ���� �Է��߱��ѵ� SA ����� ������ �����
	int select;
	if (is_show_SA == YES)
	{
		if (STRING_INPUT(active_zero_message))
		{
			SET_COLOR(ACTIVE_ZERO_COLOR);
			printf("[%03d] -> %s\n", UNIVERSAL_ZERO, active_zero_message);
			SET_COLOR_DEFAULT;
		}
		Show_SA(root, SITE_ONLY);
		if (STRING_INPUT(general_message))
			printf("%s\n", general_message);
	}
	INPUT_SELECT;
	switch (select)
	{
	case NO_INPUT://�ƹ� �Է¾��� ���� ġ��
		return NO_INPUT;
	case NOT_A_NUMBER://���ڸ��� ���� �Է�������
		return NOT_A_NUMBER;
	default:
		if (select > root->how_many_sites || select < 0) //���� �Է��߱��ѵ� ������ �����
			return OUT_OF_RANGE;
		return select;
	}
}
int Select_AE_Number(Site_Account * SA, char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH], int is_show_AE)
{	//��ȯ�� �� �˻��ؾ��� ���
	//1. �ƹ� �Է¾��� ���͸� ĥ ���
	//2. ���ڸ��� ���� �Է����� ���
	//3. ���� �Է��߱��ѵ� AE ����� ������ �����
	int select;
	if (is_show_AE == YES)
	{
		if (STRING_INPUT(active_zero_message))
		{
			SET_COLOR(ACTIVE_ZERO_COLOR);
			printf("[%03d] -> %s\n", UNIVERSAL_ZERO, active_zero_message);
			SET_COLOR_DEFAULT;
		}
		Show_AE(SA);
		if (STRING_INPUT(general_message))
			printf("%s\n", general_message);
	}
	INPUT_SELECT;
	switch (select)
	{
		case NO_INPUT:
			return NO_INPUT;
		case NOT_A_NUMBER:
			return NOT_A_NUMBER;
		default:
			if (select > SA->how_many_accounts || select < 0)
				return OUT_OF_RANGE;
			return select;
	}
}
int Select_AE_Attribute(char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH])
{
	int select;
	char * attribute_list[] = { "ID","PW","MM" };
	if (STRING_INPUT(active_zero_message))
	{
		SET_COLOR(ACTIVE_ZERO_COLOR);
		printf("[%03d] -> %s\n", UNIVERSAL_ZERO, active_zero_message);
		SET_COLOR_DEFAULT;
	}
	for (int i = 0; i < sizeof(attribute_list) / sizeof(char*); i++)
		printf("[%03d] -> %s ����.\n", i + 1, attribute_list[i]);
	if (STRING_INPUT(general_message))
		printf("%s\n", general_message);
	INPUT_SELECT;
	switch (select)
	{
		case NO_INPUT:
			return NO_INPUT;
		case NOT_A_NUMBER:
			return NOT_A_NUMBER;
		default:
			if (select > sizeof(attribute_list) / sizeof(char*) || select < 0)
				return OUT_OF_RANGE;
			return select;
	}
}
//Select....() ;

//Attach....() -> SA�� DB��, Ȥ�� AE�� SA�� ���δ�.
void Attach_AE_to_the_SA(Account_Element* AE_to_insert, Site_Account* SA)
{
	if (AE_to_insert == NULL || SA == NULL)
		printf("Attach_AE_to_the_Site_Account() ����\n");
	else
	{
		if (SA->head == NULL)
			SA->head = AE_to_insert;
		else
		{
			Account_Element * seek_end = SA->head;
			while (seek_end->next != NULL)
				seek_end = seek_end->next;
			seek_end->next = AE_to_insert;
		}
		SA->how_many_accounts++;
	}
}
void Attach_SA_to_the_DB(Site_Account* SA_to_insert, DB* root)
{
	if (SA_to_insert == NULL || root == NULL)
		printf("Attach_SA_to_the_Database() ����\n");
	else
	{
		if (root->first_Site == NULL)
			root->first_Site = SA_to_insert;
		else
		{
			Site_Account * seek_end = root->first_Site;
			while (seek_end->next != NULL)
				seek_end = seek_end->next;
			seek_end->next = SA_to_insert;
		}
		root->how_many_sites++;
	}
}
//Attach....() ;

//Fill....() -> SA Ȥ�� AE�� �������� ������ ä���ִ´�.
Site_Account * Fill_the_SA_Form()
{
	char buffer[COMMON_LENGTH] = { 0 };
	printf("����Ʈ �̸� �Է� : ");
	SET_COLOR(ORDER_COLOR);
	gets_s(buffer, SITE_NAME_LENGTH);
	SET_COLOR_DEFAULT;
	if (NO_STRING_INPUT(buffer))
		return (Site_Account*)NO_INPUT;
	if (IMPROPER_INPUT(buffer))
		return (Site_Account*)SYSTEM_CHAR_INPUT;
	Site_Account * new_SA = (Site_Account*)malloc(sizeof(Site_Account)); 
	if (new_SA == (Site_Account*)NULL)
	{
		free(new_SA);
		return (Site_Account*)NOTHING_POINTER;
	}
	strcpy_s(new_SA->Site_Name, SITE_NAME_LENGTH, buffer);
	new_SA->how_many_accounts = 0;
	new_SA->next = NULL;
	new_SA->head = NULL;
	return new_SA;
}
Account_Element * Fill_the_AE_Form()
{
	Account_Element * new_AE = (Account_Element*)malloc(sizeof(Account_Element));
	if (new_AE == NULL)
		return NOTHING_POINTER;
	char buffer[COMMON_LENGTH] = { 0 };
	char * string_array[] = { "ID", "PW", "MM" };
	for (int each_subject = 0; each_subject < sizeof(string_array) / sizeof(char*); each_subject++)
	{
		printf("\t%s ? ",string_array[each_subject]);
		SET_COLOR(ORDER_COLOR);
		gets_s(buffer, COMMON_LENGTH);
		SET_COLOR_DEFAULT;
		if (NO_STRING_INPUT(buffer))
		{
			if ((!strcmp(string_array[each_subject], "ID")) || (!strcmp(string_array[each_subject], "PW")))	//ID�� PW�� ������������ �Է���ҷ� ����
			{
				free(new_AE);
				return (Account_Element *)NO_INPUT;
			}
			else
				;
		}
		if (IMPROPER_INPUT(buffer))
		{
			free(new_AE);
			return (Account_Element *)SYSTEM_CHAR_INPUT;
		}
		switch (each_subject)
		{
		case 0:	//ID
			strcpy_s(new_AE->ID, COMMON_LENGTH, buffer);
			break;
		case 1:	//PW
			strcpy_s(new_AE->PW, COMMON_LENGTH, buffer);
			break;
		case 2:	//MEMO
			if (NO_STRING_INPUT(buffer))
				strcpy_s(new_AE->Memo, COMMON_LENGTH, NULL_MESSAGE);
			else
				strcpy_s(new_AE->Memo, COMMON_LENGTH, buffer);
			break;
		default:
			free(new_AE);
			printf("���� �������� ����.\n");
			return (Account_Element *)NOTHING_POINTER;
		}
	}
	memset(buffer, 0, COMMON_LENGTH);
	What_Time_Is_It(buffer); //������Ʈ �ð�
	strcpy_s(new_AE->Update_Time, UPDATE_TIME_SIZE, buffer);
	new_AE->next = NULL;
	return new_AE;
}
//Fill....() ;

//Find....() -> �־��� select ��ȣ�� ������ �ش��ϴ� ������ SA �Ǵ� AE�� ã�� �ּ� ��ȯ
								//select�� �����̶�� �����ϹǷ� ���� ����ó���� ������ �ʴ´�.
Site_Account* Find_SA_Through_Number(DB * root, int select)
{
	Site_Account * find_SA = NULL;
	if (root->how_many_sites <= 0)
	{
		printf("���� DB�� ����Ʈ ����� �������� �ʽ��ϴ�.\n");
		return NOTHING_POINTER;
	}
	if (select > (root->how_many_sites) || select <= 0)
	{
		printf("������ ��ȣ�� ����Ʈ�� �������� �ʽ��ϴ�.\n"); 
		return NOTHING_POINTER;
	}
	find_SA = root->first_Site;
	while (--select)
		find_SA = find_SA->next;
	return find_SA;
}
Account_Element* Find_AE_Through_Number(Site_Account * SA, int select)
{
	Account_Element * find_AE = NULL;
	if (SA->how_many_accounts == 0)
	{
		printf("���� ����Ʈ�� ���� ����� �������� �ʽ��ϴ�.\n");
		return NOTHING_POINTER;
	}
	if (select > (SA->how_many_accounts) || select <= 0)
	{
		printf("������ ��ȣ�� ����Ʈ�� �������� �ʽ��ϴ�.\n");
		return NOTHING_POINTER;
	}
	find_AE = SA->head;
	while (--select)
		find_AE = find_AE->next;
	return find_AE;
}
//Find....() ;

//Delete....()
int Delete_SA_From_DB(Site_Account * SA_to_delete, DB * root)
{
	if (SA_to_delete == NULL || root == NULL)
		return FAIL;
	if (root->first_Site == SA_to_delete)
		root->first_Site = SA_to_delete->next;
	else
	{
		Site_Account * before_SA_to_delete = root->first_Site;
		while (before_SA_to_delete->next != SA_to_delete)
			before_SA_to_delete = before_SA_to_delete->next;
		before_SA_to_delete->next = SA_to_delete->next;
	}
	free(SA_to_delete);
	return SUCCESS;
}
int Delete_AE_From_SA(Account_Element* AE_to_delete, Site_Account* SA)
{
	if (AE_to_delete == NULL || SA == NULL)
		return FAIL;
	if (SA->head == AE_to_delete)
		SA->head = AE_to_delete->next;
	else
	{
		Account_Element * before_AE_to_delete = SA->head;
		while (before_AE_to_delete->next != AE_to_delete)
			before_AE_to_delete = before_AE_to_delete->next;
		before_AE_to_delete->next = AE_to_delete->next;
	}		
	free(AE_to_delete);
	return SUCCESS;
}
//Delete....() ;