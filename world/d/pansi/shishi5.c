// ������ ��ϼ���Ӱ�����ֵĵص�
// by lestat

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
��������ϼ���ӵ��Է���ÿ��ҹĻ���ٵ�ʱ����ϼ���ӾͲ�֪ȥ���ˡ�
LONG );
	set("exits", ([
		"up" : __DIR__"shishi4",
	]));
	set("objects",([
		"/d/pansi/obj/yinsuo.c":1, 
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
