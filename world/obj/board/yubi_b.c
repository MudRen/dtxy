
inherit BULLETIN_BOARD;
void create()
{
set_name("����ɽ���", ({ "board" }) );
set("location", "/d/kunlun/gate");
  set("board_id", "yubi_b");
  set("long",     "����һ�������羵��ʯ�ڡ�\n" );
  setup();
  set("capacity", 100);
  replace_program(BULLETIN_BOARD);
}

