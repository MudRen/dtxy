// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// Room: /d/nanhai/zhulin
inherit ROOM;

void create ()
{
  set ("short", "������");
  set ("long", @LONG

���Ӻ�ɽ�������֡�Ҳ�ǹ������������������ڡ�����ϸ�裬
���΢���������ڴˣ�����֮���Ŷ�ʱ������ɢ����������һ
С������
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"pool",
  "east" : __DIR__"zhulin24",
]));

  setup();
  replace_program(ROOM);
}
