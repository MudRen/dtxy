// Room: /d/nanhai/xiaol3.c

inherit ROOM;

void create()
{
	set("short", "С·");
	set("long", @LONG

����һ��ͨ����ɽ��С·����·����Խ��Խ�����ߣ��ֲ�ҲԽ��Խ���ˡ�
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "south" : __DIR__"xiaol2",
  "northeast" : __DIR__"road4",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
