inherit BULLETIN_BOARD;

void create()
{
	set_name("�������԰�", ({ "board" }) );
	set("location", "/d/city/giftroom");
	set("long",	"����һ�����˼�¼���������˵����԰塣\n" );
set("board_id", "biwuboard");
	setup();
	set("capacity", 200);
	replace_program(BULLETIN_BOARD);
}


