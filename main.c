#include "all_included.h"

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
	switch (Convert_Orderset_to_Interger(Order))
	{
		case show_site_list:
			Show_SA(root, SITE_ONLY);
			break;

		case show_account_list:
			Show_SA(root, SITE_AND_ACCOUNTS);
			break;

		case add_something:
			Add(root);
			break;

		case update_something:
			Update(root);
			break;

		case delete_something:
			Delete(root);
			break;

		case swap_site_order:
			Swap_Site_Order(root);
			break;

		case export_data:
			Export_DB(root);
			break;

		case help:
			How_To_Use_Operations();
			break;

		case clear_display:
			system("cls");
			break;

		case quite_program:
			Quit_Program(root);
			break;

		case no_input:
			DO_NOTHING;
			break;

		case	undefined_order:
			printf("유효하지 않은 명령\n");
			break;

		case show_account_through_number:
			Show_Accounts_Relevant_Site_Number(root, Order);
			break;
			//////////////////여기서부턴 평범하지 않은 명령어 (거의 디버깅)///////////////////
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
			SET_COLOR(ORDER_COLOR);
			gets_s(Order, ORDER_LENGTH);
			SET_COLOR_DEFAULT;
		}
		Operation_System(&is_loaded, Order);
	}
	return 0;
}