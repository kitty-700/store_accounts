void Add(DB * root);
void Update(DB	* root);
void Delete(DB * root);
void Swap_Site_Order(DB * root);
int History_Show();
void History_Add(int order_number, const char str_1[COMMON_LENGTH], const char str_2[COMMON_LENGTH]);
	//��� �̰� ������� �Ǵ°� �ƴϴ�.
void Reload(DB * root, int * is_loaded);
void Quit_Program(DB * root);
int How_To_Use_Operations();
