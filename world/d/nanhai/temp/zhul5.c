
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
  "northwest" : __DIR__"zhul"+sprintf("%d", random(6)),
  "northeast" : __DIR__"zhuli0",
  "south" : __DIR__"zhul"+sprintf("%d", random(6)),
]));

   setup();
   replace_program(ROOM);
}
