
inherit BULLETIN_BOARD;
void create()
{
        set_name(" ���� ", ({ "jianbei" }) );
        set("location", "/d/sanxian/jianzhong.c");
        set("board_id", "jian_b");
     set("long",     "һ��޴��ʯ��,ǡ��һ�ѳ������뽣�V��\n" );
        setup();
        set("capacity", 80);
        replace_program(BULLETIN_BOARD);
}

