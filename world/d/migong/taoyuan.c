// taoyuan.c
//tomcat
inherit ROOM;

void create()
{
	set("short", "������Դ");
	set("long", @LONG
�������������Դ��
LONG
	);
	set("no_clean_up", 0);

	set("exits",([
	"east" : __DIR__"zhanchang/exit",
]));
set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/shenlu" : 1,
        ]));
	setup();
	replace_program(ROOM);
}

