// nancheng_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("���������", ({ "board" }) );
	set("location", "/d/city/yimin");
	set("board_id", "yimin");
	set("long",	"����һ������������������԰塣\n" );
	setup();
	set("capacity", 200);
	replace_program(BULLETIN_BOARD);
}


