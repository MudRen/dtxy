// Room: /d/menggu/caoyuan2.c

inherit ROOM;

void create()
{
	set("short", "Į����ԭ");
	set("long", @LONG
���������Į����ԭ,��Ⱥ��ţ��İ����±���,���ſ����������
���������еĳ���,�����Ĳ�ԭ.�ϱ�ȥ�ǵ���ԭ,�����ȥ�������������
Ӫ��.
LONG
	);
	set("no_clean_up", 0);
	set("outdoors", "menggu");
	set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"caoyuan3",
  "north" : __DIR__"caoyuan",
]));

	setup();
	replace_program(ROOM);
}

