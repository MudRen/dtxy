
inherit BULLETIN_BOARD;
void create()
{
        set_name("  ��ʯ  ", ({ "leishi" }) );
        set("location", "/d/pansi/damen");
        set("board_id", "lei_b");
  set("long", "һ���ʯͷ�����顰��Ϊ���
������������������������������������������������������������������������\n");
        setup();
        set("capacity", 80);
        replace_program(BULLETIN_BOARD);
}

