
inherit ROOM;

void create()
{
   set("short", "������");
   set("long", @LONG

���Ӻ�ɽ�������֡�Ҳ�ǹ������������������ڡ�����ϸ�裬
���΢���������ڴˣ�����֮���Ŷ�ʱ������ɢ��
LONG
   );
   set("exits", ([ /* sizeof() == 4 */
  "enter" : __DIR__"tar1",
  "west" : "/d/nanhai/zhulin",
]));

   setup();
   replace_program(ROOM);
}
