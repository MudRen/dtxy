inherit "/adm/daemons/vrm_server";

void create()
{
	// �Թ��������̳е�����ĵ������ơ�
	set_inherit_room( WARPLACE );

	//�Թ��ĵ��߳�
	set_maze_long(5);

	//��ڷ���(�����ڶ���)
	set_entry_dir("east");

	//�������������ӷ���
	set_link_entry_dir("east");

	//�������������ӵ�����
	set_link_entry_room(__DIR__"zhanchang2");

	//��������������ӷ���
	set_link_exit_dir("west");

	//��������������ӵ�����
	set_link_exit_room(__DIR__"zhanchang1");

	//��ڷ��������
	set_entry_short("ս��");

	//��ڷ�������
	set_entry_desc(@LONG
����ս���ĳ��ء�
LONG
);

	//���ڷ��������
	set_exit_short("ս��");

	//���ڷ�������
	set_exit_desc(@LONG
����ս���ĳ��ء�
LONG
);

	//�Թ�����Ķ�����
	set_maze_room_short("ս��");

	//�Թ����������������ж�������������ÿ����
	//���ʱ���������ѡ��һ����
	set_maze_room_desc(@LONG
����ս���ĳ��ء�
LONG
);

		
}
