#include "all_included.h"
/* 커맨드라인의 명령어 체계는 main.c 에 정의되어있다. */
void Operation_System(int * is_loaded, char Order[ORDER_LENGTH])
{
	static DB * root = NULL;
	if (*is_loaded == FALSE)
	{
		root = Start_Import_Process();
		if (root == (DB*)NULL)
			BEFORE_EXIT_PRINT_("에러");
		*is_loaded = TRUE;
		return;
	}
	switch (Convert_Orderset_to_Constant(Order))
	{
		case show_site_list:	//전체 사이트 리스트만 쭉 나열한다.
			Show_SA(root, SITE_ONLY);
			break;

		case show_account_list:	//사이트 리스트에 더해, 해당 사이트의 전체 계정 리스트 역시도 나열한다.
			Show_SA(root, SITE_AND_ACCOUNTS);
			break;

		case add_something:	//사이트던 계정이던 DB에 추가한다.
			Add(root);
			break;

		case update_something:	//사이트 이름이던 계정 정보던 수정한다.
			Update(root);
			break;

		case delete_something:	//사이트던 계정이던 DB에서 삭제한다.
			Delete(root);
			break;

		case swap_site_order:	//사이트 간의 순서를 바꾼다.
			Swap_Site_Order(root);
			break;

		case export_data:		//DB 내용을 파일에 저장한다.
			Export_DB(root);
			break;

		case help:	//메뉴얼 보기
			How_To_Use_Operations();
			break;

		case clear_display:	//화면을 비운다.
			system("cls");
			break;

		case quite_program:	//프로그램을 종료하지만, 변경 사항이 있을 경우 저장할지 확인한다.
			Quit_Program(root);
			break;

		case show_account_through_number:		/*명령으로 숫자만 입력할 경우의 특수행동을 정의한다.
			입력이 0일 경우는 case show_site_list : 와 같고, 
			나머지는 해당 번호를 가진 사이트 계정들을 출력.  (범위 초과하면 아무것도 안 함)*/
			Show_Accounts_Relevant_Site_Number(root, Order);
			break;

		case	undefined_order:
			printf("유효하지 않은 명령\n");
			break;

			//////////////////여기서부턴 평범하지 않은 명령어 (거의 디버깅)///////////////////
		case no_input:
			DO_NOTHING;
			break;

		case re_import:
			Reload(root, is_loaded);
			break;

		case show_change_history:
			History_Show();
			break;

		case do_nothing:
			History_Add(HISTORY_NOTHING, "아무것도 안 한 것을 기록한다.", "");
			break;

		case unset_DB:
			Unload_DB(root);
			break;

		case unset_history:
			Unload_History();
			break;

		default:
			printf("명령어 에러!!\n");
	}
	return;
}

int main(void)
{
#if TEST_MODULE
	Module_Test();
	return 0;
#else
	char Order[ORDER_LENGTH] = { 0 };
	static int is_loaded = FALSE;
	#if DO_LOGIN_PROCESS
		Login();
		system("cls");
	#endif
	while (1)
	{
		if (is_loaded == TRUE)
		{
			PRINT_DEVIDE_THICK_LINE;
			printf("> ");
			SET_CONSOLE_COLOR(ORDER_COLOR); 
			Get_String_Without_Buffer_Overflow(Order);
			SET_CONSOLE_COLOR_DEFAULT;
		}
		Operation_System(&is_loaded, Order);
	}
	return 0;
#endif
}