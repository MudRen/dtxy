// nancheng_b.c

inherit BULLETIN_BOARD;

void create()
{
set_name("���ƶ����԰�", ({ "huoyun" }) );
set("location", "/d/qujing/kusong/guaishiya");
        set("board_id", "hyd_b");
	set("long",	"����һ���������Լ��µ����԰塣\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
