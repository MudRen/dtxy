inherit BULLETIN_BOARD;

void create()
{
        set_name("�������԰�", ({ "board" }) );
        set("location", "/u/rico/home");
        set("long",     "����һ�������������Ե����԰塣\n" );
set("board_id", "qilinboard");
        setup();
        set("capacity", 200);
        replace_program(BULLETIN_BOARD);
}
