// Cracked by �辪ѩ 4-15-2002
inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
���������ӹ�����Ļ�·������Զ���������ϡ�١�
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"huanglu1",
  "northeast" : __DIR__"huanglu3",
]));
	set("outdoors", "menggu");
	setup();
	replace_program(ROOM);
}

