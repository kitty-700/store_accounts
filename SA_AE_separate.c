#include "all_included.h"

//Show....() -> 내용 출력
void Show_SA(const DB * root, const int present_what_section)
{
	int count = 1;
	if (root->first_Site == NULL)
		printf("현재 등록된 사이트가 하나도 없습니다.\n");
	else
	{
		Site_Account * each_site = root->first_Site;
		while (each_site != NULL)
		{
			SET_COLOR(SITE_BASIC_COLOR);
			printf("[%03d] %s    ( %d 계정 보유 중)\n", count++, each_site->Site_Name, each_site->how_many_accounts);
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
		printf("현재 사이트 %s에 등록된 계정이 하나도 없습니다.\n", SA->Site_Name);
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

/*Select....() -> 선택한 것의 번호를 반환. 
여기서의 buffer는 입력받기 전에 하고 싶은 말, 
active_zero_message는 0번을 선택했을 경우의 메세지
*/
int Select_SA_Number(DB * root, char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH], int is_show_SA)
{	//반환된 값 검사해야할 경우
	//1. 아무 입력없이 엔터를 칠 경우
	//2. 숫자말고 딴거 입력했을 경우
	//3. 숫자 입력했긴한데 SA 목록의 범위를 벗어나면
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
	case NO_INPUT://아무 입력없이 엔터 치면
		return NO_INPUT;
	case NOT_A_NUMBER://숫자말고 딴거 입력했으면
		return NOT_A_NUMBER;
	default:
		if (select > root->how_many_sites || select < 0) //숫자 입력했긴한데 범위를 벗어나면
			return OUT_OF_RANGE;
		return select;
	}
}
int Select_AE_Number(Site_Account * SA, char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH], int is_show_AE)
{	//반환된 값 검사해야할 경우
	//1. 아무 입력없이 엔터를 칠 경우
	//2. 숫자말고 딴거 입력했을 경우
	//3. 숫자 입력했긴한데 AE 목록의 범위를 벗어나면
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
		printf("[%03d] -> %s 변경.\n", i + 1, attribute_list[i]);
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

//Attach....() -> SA를 DB에, 혹은 AE를 SA에 붙인다.
void Attach_AE_to_the_SA(Account_Element* AE_to_insert, Site_Account* SA)
{
	if (AE_to_insert == NULL || SA == NULL)
		printf("Attach_AE_to_the_Site_Account() 에러\n");
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
		printf("Attach_SA_to_the_Database() 에러\n");
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

//Fill....() -> SA 혹은 AE의 개별적인 내용을 채워넣는다.
Site_Account * Fill_the_SA_Form()
{
	char buffer[COMMON_LENGTH] = { 0 };
	printf("사이트 이름 입력 : ");
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
			if ((!strcmp(string_array[each_subject], "ID")) || (!strcmp(string_array[each_subject], "PW")))	//ID나 PW는 들어오지않으면 입력취소로 간주
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
			printf("아직 구현되지 않음.\n");
			return (Account_Element *)NOTHING_POINTER;
		}
	}
	memset(buffer, 0, COMMON_LENGTH);
	What_Time_Is_It(buffer); //업데이트 시각
	strcpy_s(new_AE->Update_Time, UPDATE_TIME_SIZE, buffer);
	new_AE->next = NULL;
	return new_AE;
}
//Fill....() ;

//Find....() -> 주어진 select 번호를 가지고 해당하는 순서의 SA 또는 AE를 찾아 주소 반환
								//select는 정상이라고 가정하므로 따로 예외처리는 해주지 않는다.
Site_Account* Find_SA_Through_Number(DB * root, int select)
{
	Site_Account * find_SA = NULL;
	if (root->how_many_sites <= 0)
	{
		printf("현재 DB에 사이트 목록이 존재하지 않습니다.\n");
		return NOTHING_POINTER;
	}
	if (select > (root->how_many_sites) || select <= 0)
	{
		printf("선택한 번호의 사이트는 존재하지 않습니다.\n"); 
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
		printf("현재 사이트에 계정 목록이 존재하지 않습니다.\n");
		return NOTHING_POINTER;
	}
	if (select > (SA->how_many_accounts) || select <= 0)
	{
		printf("선택한 번호의 사이트는 존재하지 않습니다.\n");
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