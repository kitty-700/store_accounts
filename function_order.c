#include "all_included.h"

static History history = { NULL,NULL,0 };
History * clue = &history;

void Add(DB * root)
{
	system("cls");
	int select_in_first_page;	///사이트를 새로 만들 것인지 기존의 사이트에 계정을 추가할 것인지 선택함.
	select_in_first_page = Select_SA_Number(root,
		/*입력받기 전에 출력할 도움 메세지*/	"계정을 추가하고자 하는 사이트 번호 혹은 '0'을 입력하세요.",
										/*0번 선택시*/	"새로운 사이트 등록.",
		SHOW_LIST);
	Site_Account * new_SA = NULL;
	Account_Element * new_AE = NULL;
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	switch (select_in_first_page)
	{
		case COMMON_CANCEL_REASON(추가);
		case MAKE_NEW_SITE:
			new_SA = Fill_the_SA_Form();
			if (new_SA == (Site_Account *)NO_INPUT)
				BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(추가));
			if (new_SA == (Site_Account *)SYSTEM_CHAR_INPUT)
				BEFORE_RETURN_PRINT_(MESSAGE_SYSTEM_INVAIDING_INPUT(추가));
			if (new_SA == (Site_Account *)NOTHING_POINTER)
				BEFORE_RETURN_PRINT_(MESSAGE_UNKNOWN_ERROR(추가));
			/*┌함수 성공┐*///-> 사이트 추가 성공
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 사이트 추가", root->how_many_sites + 1, new_SA->Site_Name);
			sprintf_s(history_record_2, COMMON_LENGTH, "");
			Attach_SA_to_the_DB(new_SA, root);
			History_Add(HISTORY_ADD, history_record_1, history_record_2);
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(사이트 추가));
			/*└함수 성공┘*/
		default: //이미 존재하는 사이트를 선택했다면
			new_SA = Find_SA_Through_Number(root, select_in_first_page);
			if (new_SA == NOTHING_POINTER)
				BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(추가));
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 사이트에 계정 추가", select_in_first_page, new_SA->Site_Name);

	}
	__________PRINT_DEVIDE_LINE__________;
	new_AE = Fill_the_AE_Form();
	if (new_AE == (Account_Element *)NO_INPUT)
		BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(추가));
	if (new_AE == (Account_Element *)SYSTEM_CHAR_INPUT)
		BEFORE_RETURN_PRINT_(MESSAGE_SYSTEM_INVAIDING_INPUT(추가));
	if (new_AE == (Account_Element *)NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_UNKNOWN_ERROR(추가));
	/*┌함수 성공┐*///-> 계정 추가 성공
	Attach_AE_to_the_SA(new_AE, new_SA);
	sprintf_s(history_record_2, COMMON_LENGTH, "\t[%03d]\tID : %s\n\t\t\tPW : %s", FIRST, new_AE->ID, new_AE->PW);
	//↑ 여기서 버퍼가 터질 확률이 2배지만 일단 보류하는 것으로
	History_Add(HISTORY_ADD, history_record_1, history_record_2);
	BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(계정 추가));
	/*└함수 성공┘*/
}
void Update(DB * root)
{
	if (DB_EMPTY)
		BEFORE_RETURN_PRINT_("DB가 비어있으므로 업데이트 취소.\n"); 
	system("cls");
	int select_in_first_page;		///업데이트할 사이트를 선택함.
	int select_in_second_page;	///사이트 이름을 업데이트 할 것인지 사이트 내의 계정을 업데이트할 것인지 선택함.
	int select_in_third_page;		///사이트 내 계정의 어떠한 요소를 업데이트할 것인지 선택함.
	MAKE_BUFFER(string_to_be_replaced);
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	select_in_first_page = Select_SA_Number(root,
		/*입력받기 전에 출력할 도움 메세지*/	"업데이트 할 사이트 번호 혹은 '0'을 입력하세요.",
										/*0번 선택시*/	"업데이트 취소.",
		SHOW_LIST);
	switch (select_in_first_page)
	{
		case COMMON_CANCEL_REASON(업데이트);
		case CANCEL_UPDATE:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(업데이트));
	}
	Site_Account * to_be_updated_SA = Find_SA_Through_Number(root, select_in_first_page);
	if (to_be_updated_SA == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(업데이트));
	system("cls");
	SET_COLOR(SITE_BASIC_COLOR);
	printf("선택됨 > [%03d] %s\n", select_in_first_page, to_be_updated_SA->Site_Name);
	SET_COLOR_DEFAULT;
	__________PRINT_DEVIDE_LINE__________;
	select_in_second_page = Select_AE_Number(to_be_updated_SA,
		/*입력받기 전에 출력할 도움 메세지*/	"업데이트 할 계정 번호 혹은 '0'을  입력하세요.",
										/*0번 선택시*/	"선택한 사이트 이름 변경",
		SHOW_LIST);
	switch (select_in_second_page)
	{
		case COMMON_CANCEL_REASON(업데이트);
		case CHANGE_SITE_NAME:
			//UNIVERSAL_ZERO == 0
			printf("\tSite Name : %s -> ? ", to_be_updated_SA->Site_Name);
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d]\t\" %s \" 사이트의 이름을", select_in_first_page, to_be_updated_SA->Site_Name);
			SET_COLOR(ORDER_COLOR);
			gets_s(string_to_be_replaced, SITE_NAME_LENGTH);
			SET_COLOR_DEFAULT;
			COMMON_STRING_INPUT_CANCEL_REASON(string_to_be_replaced, 업데이트);
			strcpy_s(to_be_updated_SA->Site_Name, SITE_NAME_LENGTH, string_to_be_replaced);
			sprintf_s(history_record_2, COMMON_LENGTH, "\t\" %s \" 로 업데이트했습니다.", to_be_updated_SA->Site_Name);
			/*┌함수 성공┐*///-> 사이트 이름 업데이트 성공
			History_Add(HISTORY_UPDATE, history_record_1, history_record_2);
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(업데이트));
			/*└함수 성공┘*/
	}
	Account_Element * update_AE = Find_AE_Through_Number(to_be_updated_SA, select_in_second_page);
	if (update_AE == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(업데이트));
	system("cls"); 
	SET_COLOR(SITE_BASIC_COLOR);
	printf("선택됨 > [%03d] %s\n", select_in_first_page, to_be_updated_SA->Site_Name);
	SET_COLOR_DEFAULT;
	SET_COLOR(ACCOUNT_BASIC_COLOR);
	printf("선택됨 > [%03d]\n\tID :%s\n", select_in_second_page, update_AE->ID);
	SET_COLOR_DEFAULT;
	__________PRINT_DEVIDE_LINE__________;
	select_in_third_page = Select_AE_Attribute(
		/*입력받기 전에 출력할 도움 메세지*/	"업데이트 할 항목의 번호 혹은 '0'을 입력하세요.",
										/*0번 선택시*/	"업데이트 작업 취소.");
	switch (select_in_third_page)
	{
		case COMMON_CANCEL_REASON(업데이트);
		case CANCEL_UPDATE:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(업데이트));
	}
	switch (select_in_third_page)
	{
	case 1: //ID 변경
		printf("\tID : %s -> ? ", update_AE->ID);
		break;
	case 2: //PW 변경
		printf("\tPW : %s -> ? ", update_AE->PW);
		break;
	case 3: //메모 변경
		printf("\tMEMO : %s -> ? ", update_AE->Memo);
		break;
	default: //에러 (나올 수 없음.)
		BEFORE_RETURN_PRINT_("에러!!\n");
	}
	SET_COLOR(ORDER_COLOR);
	gets_s(string_to_be_replaced, COMMON_LENGTH);
	SET_COLOR_DEFAULT;
	COMMON_STRING_INPUT_CANCEL_REASON(string_to_be_replaced, 업데이트);
	switch (select_in_third_page)
	{
	case 1: //ID 변경
		sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 사이트의\n\t\t[%03d] ID : %s 의 ID 를\n\t\t\t\" %s \" 에서",
			select_in_first_page, to_be_updated_SA->Site_Name, select_in_second_page, update_AE->ID, update_AE->ID);
		strcpy_s(update_AE->ID, ID_LENGTH, string_to_be_replaced); 
		break;
	case 2: //PW 변경
		sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 사이트의\n\t\t[%03d] ID : %s 의 PW 를\n\t\t\t\" %s \" 에서",
			select_in_first_page, to_be_updated_SA->Site_Name, select_in_second_page, update_AE->ID, update_AE->PW);
		strcpy_s(update_AE->PW, PASSWORD_LENGTH, string_to_be_replaced); 
		break;
	case 3: //메모 변경
		sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 사이트의\n\t\t[%03d] ID : %s 의 Memo 를\n\t\t\t\" %s \" 에서",
			select_in_first_page, to_be_updated_SA->Site_Name, select_in_second_page, update_AE->ID, update_AE->Memo);
		strcpy_s(update_AE->Memo, MEMO_LENGTH, string_to_be_replaced); 
		break;
	}
	sprintf_s(history_record_2, COMMON_LENGTH, "\t\t\" %s \" 로 변경.", string_to_be_replaced);
	/*┌함수 성공┐*///-> 계정 정보 업데이트 성공
	What_Time_Is_It(string_to_be_replaced);
	strcpy_s(update_AE->Update_Time, COMMON_LENGTH, string_to_be_replaced);
	History_Add(HISTORY_UPDATE, history_record_1, history_record_2);
	BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(업데이트));
	/*└함수 성공┘*/
}

void Delete(DB * root)
{
	if (DB_EMPTY)
		BEFORE_RETURN_PRINT_("DB가 비어있으므로 삭제 취소.\n");
	//DB에 자료가 존재하는지 검사///////////////////////////////////////////
	system("cls");
	int select_in_first_page;		///어떤 사이트 내용을 삭제할 것인지 선택함.
	int select_in_second_page;	///사이트 자체를 삭제할 것인지 사이트 내의 어떤 계정 하나를 삭제할 것인지 선택함.
	select_in_first_page = Select_SA_Number(root,
		/*입력받기 전에 출력할 도움 메세지*/	"삭제할 사이트 번호 혹은 '0'을 입력하세요.",
										/*0번 선택시*/	"삭제 취소.",
		SHOW_LIST);
	switch (select_in_first_page)
	{
		case COMMON_CANCEL_REASON(삭제);
		case CANCEL_DELETE:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(삭제));
	}
	Site_Account * delete_SA = Find_SA_Through_Number(root, select_in_first_page);
	if (delete_SA == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(삭제));
	system("cls");
	SET_COLOR(SITE_BASIC_COLOR);
	printf("선택됨 > [%03d] %s\n", select_in_first_page, delete_SA->Site_Name);
	SET_COLOR_DEFAULT;
	__________PRINT_DEVIDE_LINE__________;
	select_in_second_page = Select_AE_Number(delete_SA,
		/*입력받기 전에 출력할 도움 메세지*/	"삭제할 할 계정 번호 혹은 '0'을  입력하세요.",
										/*0번 선택시*/	"선택한 사이트 삭제.",
		SHOW_LIST);
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	switch (select_in_second_page)
	{
		case COMMON_CANCEL_REASON(삭제);
		case DELETE_SITE:
		{
			if (Ask_Continue("삭제하시겠습니까 ?") == FALSE)
				BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(삭제));
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 사이트를 삭제했습니다.", select_in_first_page, delete_SA->Site_Name);
			sprintf_s(history_record_2, COMMON_LENGTH, "");
			if (Delete_SA_From_DB(delete_SA, root) == FAIL)
				BEFORE_RETURN_PRINT_(MESSAGE_FAIL(삭제));
			/*┌함수 성공┐*///-> 사이트 삭제 성공
			History_Add(HISTORY_DELETE, history_record_1, history_record_2);
			root->how_many_sites--;
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(삭제));
			/*└함수 성공┘*/
		}
		default: //0번이 아니라 계정 번호를 선택했을 경우
		{
			sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 사이트의", select_in_first_page, delete_SA->Site_Name);
			Account_Element * delete_AE = Find_AE_Through_Number(delete_SA, select_in_second_page);
			if (delete_AE == NOTHING_POINTER)
				BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(삭제));
			system("cls");
			SET_COLOR(SITE_BASIC_COLOR);
			printf("선택됨 > [%03d] %s\n", select_in_first_page, delete_SA->Site_Name);
			SET_COLOR_DEFAULT;
			SET_COLOR(ACCOUNT_BASIC_COLOR);
			printf("선택됨 > [%03d]\n\tID :%s\n", select_in_second_page, delete_AE->ID);
			SET_COLOR_DEFAULT;
			printf("\tPW :%s\n", delete_AE->PW);
			printf("\tUD :%s\n", delete_AE->Update_Time);
			printf("\tMM :%s\n", delete_AE->Memo);
			__________PRINT_DEVIDE_LINE__________;
			if (Ask_Continue("삭제하시겠습니까?") == FALSE)
				BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(삭제));
			sprintf_s(history_record_2, COMMON_LENGTH, "\t[%03d] ID : %s 계정을 삭제했습니다.", select_in_second_page, delete_AE->ID);
			if (Delete_AE_From_SA(delete_AE, delete_SA) == FAIL)
				BEFORE_RETURN_PRINT_(MESSAGE_FAIL(삭제)); 
			/*┌함수 성공┐*///-> 계정 삭제 성공
			History_Add(HISTORY_DELETE, history_record_1, history_record_2);
			delete_SA->how_many_accounts--;
			BEFORE_RETURN_PRINT_(MESSAGE_SUCCESS(삭제));
			/*└함수 성공┘*/
		}
	}
}
void Swap_Site_Order(DB * root)
{
	if (DB_EMPTY)
		BEFORE_RETURN_PRINT_("DB가 비어있으므로 삭제 취소.\n");
	//DB에 자료가 존재하는지 검사///////////////////////////////////////////
	system("cls");
	int select_1, select_2;
	Site_Account * SA_1 = NULL;
	Site_Account * SA_2 = NULL;
	select_1 = Select_SA_Number(root,
		/*입력받기 전에 출력할 도움 메세지*/	"교환할 사이트의 번호 혹은 '0'을 입력하세요",
										/*0번 선택시*/	"교환 취소",
		SHOW_LIST);
	switch (select_1)
	{
		case COMMON_CANCEL_REASON(교환);
		case CANCEL_SWAP:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(교환));
	}
	select_2 = Select_SA_Number(root,
		/*입력받기 전에 출력할 도움 메세지*/	"교환할 사이트의 번호 혹은 '0'을 입력하세요",
										/*0번 선택시*/	"교환 취소",
		DONT_SHOW_LIST);
	switch (select_2)
	{
		case COMMON_CANCEL_REASON(교환);
		case CANCEL_SWAP:
			BEFORE_RETURN_PRINT_(MESSAGE_CANCEL(교환));
	}
	if (select_1 == select_2)
		BEFORE_RETURN_PRINT_("동일한 사이트입니다.\n");
	if (select_1 > select_2) //select_1이 더 낮은 번호여야 한다. 그래야 구현 편함.
	{	//swap select_1 and select_2
		int temp_select = select_1;
		select_1 = select_2;
		select_2 = temp_select;
	}
	SA_1 = Find_SA_Through_Number(root, select_1);
	if (SA_1 == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(교환));
	SA_2 = Find_SA_Through_Number(root, select_2);
	if (SA_2 == NOTHING_POINTER)
		BEFORE_RETURN_PRINT_(MESSAGE_WRONG_INPUT(교환));
	{	//두 포인터를 바꾸는 루틴은 이 중괄호 내에
		Site_Account * previous_of_SA_1 = root->first_Site;
		Site_Account * previous_of_SA_2 = SA_1;	///어차피 SA_2는 최소한 swap_SA_1 보다 번호가 높을 것이기 때문
		while (previous_of_SA_2->next != SA_2)
			previous_of_SA_2 = previous_of_SA_2->next;
		if (SA_1 != root->first_Site)	///swap_SA_1 이 맨 첫번째 SA인데 그 전의 SA 라는 개념이 있으면 안 되니까.
		{
			while (previous_of_SA_1->next != SA_1)
				previous_of_SA_1 = previous_of_SA_1->next;
			previous_of_SA_1->next = SA_2;									///-> 이 때에만 previous_of_SA_1이 작용할 수 있다.
		}
		else			//SA_1이 DB 내의 첫번째 SA라면?
			root->first_Site = SA_2;
		if (SA_1 == previous_of_SA_2)	//SA_2의 바로 전이 SA_1일 경우
		{
			SA_1->next = SA_2->next;
			SA_2->next = SA_1;
		}
		else if (SA_1 != previous_of_SA_2)	//SA_2의 바로 전이 SA_1이 아닐 경우
		{
			Site_Account * SA_temp = SA_1->next;
			SA_1->next = SA_2->next;
			SA_2->next = SA_temp;
			previous_of_SA_2->next = SA_1;
		}
	}
	//이건 어떻게 성공했는지 검증할지 잘 모름
	MAKE_BUFFER(history_record_1);
	MAKE_BUFFER(history_record_2);
	SET_COLOR(SITE_BASIC_COLOR);
	printf("[%03d] %s ", select_1, SA_1->Site_Name);
	SET_COLOR_DEFAULT;
	printf("와(/과) \n");
	SET_COLOR(SITE_BASIC_COLOR);
	printf("[%03d] %s ", select_2, SA_2->Site_Name);
	SET_COLOR_DEFAULT;
	printf("의 위치를 교환했습니다.\n");
	sprintf_s(history_record_1, COMMON_LENGTH, "[%03d] %s 와(/과)", select_1, SA_1->Site_Name);
	sprintf_s(history_record_2, COMMON_LENGTH, "[%03d] %s 의 위치를 교환했습니다.", select_2, SA_2->Site_Name);

	History_Add(HISTORY_SWAP, history_record_1, history_record_2);
}
void History_Add(int order_number, const char str_1[COMMON_LENGTH], const char str_2[COMMON_LENGTH])
{	//1~2개의 문자열을 CS 구조체에 단순히 붙이는 정도
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
	/* 함수 사용
	MAKE_BUFFER(buffer_1);
	MAKE_BUFFER(buffer_2);
	sprintf_s(buffer_1, COMMON_LENGTH, "[%03d] %s 와(/과)", select_1, SA_1->Site_Name);
	sprintf_s(buffer_2, COMMON_LENGTH, "[%03d] %s 의 위치를 교환했습니다.", select_2, SA_2->Site_Name);
	History_Add(HISTORY_SWAP, buffer_1, buffer_2);
	/*┌함수 성공┐
	/*└함수 성공┘*/
}
int History_Show()
{
	if (HISTORY_EMPTY)
		BEFORE_RETURN_INTEGER_PRINT_("변경 사항 없습니다.\n", FALSE);
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
			printf("에러\n");
			break;
		}
		if (STRING_INPUT(temp_CS->change_from))
			printf("\t%s\n", temp_CS->change_from);
		if (STRING_INPUT(temp_CS->change_to))
			printf("\t%s\n", temp_CS->change_to);
		temp_CS = temp_CS->next;
	}
	printf("\n총 %d 번의 데이터 변경 명령이 있었습니다.\n", clue->how_many_changes);
	SET_COLOR_DEFAULT;
	return TRUE;
}

int How_To_Use_Operations()
{	//Help
	__________PRINT_DEVIDE_LINE__________;
	printf("%s  / %s 버전!\n", __DATE__, __TIME__);
#if SHOW_SOURCE
	printf("kitty 제작, 메일은 knukit@naver.com 으로\n");
#endif
	printf("%s\n", HELP_MESSAGE);
	__________PRINT_DEVIDE_LINE__________;
	printf("%-10s (s)\t:리스트 보기\n", "ls");
	printf("%-10s (a)\t:사이트 혹은 계정 추가하기\n", "add");
	printf("%-10s (d)\t:사이트 혹은 계정 삭제하기\n", "del");
	printf("%-10s (u)\t:사이트 혹은 계정 변경하기\n", "upate");
	printf("%-10s (w)\t:사이트 순서 변경\n", "swap");
	printf("%-10s (l)\t:변경 사항 출력\n", "history");
	printf("%-10s (c)\t:화면을 깨끗하게 지우기\n", "cls");
	printf("%-10s (x)\t:모든 정보를 파일에 저장\n", "save");
	printf("%-10s (q)\t:프로그램 종료\n", "exit");

	printf("보통의 상황에서 아무 입력도 안 하고 엔터를 누르면 작업취소를 의미합니다.\n");
	printf("작업을 취소하는 것이 이상한 데이터를 집어넣는 것보다는 나을 것입니다.\n");
	return 0;
}
