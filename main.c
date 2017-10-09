#include "all_included.h"
/* Ŀ�ǵ������ ��ɾ� ü��� main.c �� ���ǵǾ��ִ�. */
void Operation_System(int * is_loaded, char Order[ORDER_LENGTH])
{
	static DB * root = NULL;
	if (*is_loaded == FALSE)
	{
		root = Start_Import_Process();
		if (root == (DB*)NULL)
			BEFORE_EXIT_PRINT_("����");
		*is_loaded = TRUE;
		return;
	}
	switch (Convert_Orderset_to_Constant(Order))
	{
		case show_site_list:	//��ü ����Ʈ ����Ʈ�� �� �����Ѵ�.
			Show_SA(root, SITE_ONLY);
			break;

		case show_account_list:	//����Ʈ ����Ʈ�� ����, �ش� ����Ʈ�� ��ü ���� ����Ʈ ���õ� �����Ѵ�.
			Show_SA(root, SITE_AND_ACCOUNTS);
			break;

		case add_something:	//����Ʈ�� �����̴� DB�� �߰��Ѵ�.
			Add(root);
			break;

		case update_something:	//����Ʈ �̸��̴� ���� ������ �����Ѵ�.
			Update(root);
			break;

		case delete_something:	//����Ʈ�� �����̴� DB���� �����Ѵ�.
			Delete(root);
			break;

		case swap_site_order:	//����Ʈ ���� ������ �ٲ۴�.
			Swap_Site_Order(root);
			break;

		case export_data:		//DB ������ ���Ͽ� �����Ѵ�.
			Export_DB(root);
			break;

		case help:	//�޴��� ����
			How_To_Use_Operations();
			break;

		case clear_display:	//ȭ���� ����.
			system("cls");
			break;

		case quite_program:	//���α׷��� ����������, ���� ������ ���� ��� �������� Ȯ���Ѵ�.
			Quit_Program(root);
			break;

		case show_account_through_number:		/*������� ���ڸ� �Է��� ����� Ư���ൿ�� �����Ѵ�.
			�Է��� 0�� ���� case show_site_list : �� ����, 
			�������� �ش� ��ȣ�� ���� ����Ʈ �������� ���.  (���� �ʰ��ϸ� �ƹ��͵� �� ��)*/
			Show_Accounts_Relevant_Site_Number(root, Order);
			break;

		case	undefined_order:
			printf("��ȿ���� ���� ���\n");
			break;

			//////////////////���⼭���� ������� ���� ��ɾ� (���� �����)///////////////////
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
			History_Add(HISTORY_NOTHING, "�ƹ��͵� �� �� ���� ����Ѵ�.", "");
			break;

		case unset_DB:
			Unload_DB(root);
			break;

		case unset_history:
			Unload_History();
			break;

		default:
			printf("��ɾ� ����!!\n");
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