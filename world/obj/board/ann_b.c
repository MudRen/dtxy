// nancheng_b.c

inherit BULLETIN_BOARD;

void create()
{
 set_name("���ŷ������԰�", ({ "board" }) );
set("location", "/d/wiz/newsroom");
 set("board_id", "ann_b");
	set("long",	"����һ���������Լ��µ����԰塣\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
