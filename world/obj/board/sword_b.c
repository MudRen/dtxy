

inherit BULLETIN_BOARD;
void create()
{
        set_name(" �⽣�� ", ({ "swordchi" }) );
        set("location", "/d/shushan/paifang.c");
       set("long",     "ֻ������ʯ������: ���������� ��\n" );
        setup();
        set("capacity", 80);
        replace_program(BULLETIN_BOARD);
}

