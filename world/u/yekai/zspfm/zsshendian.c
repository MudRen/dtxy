inherit ROOM;

void create ()
{
  set ("short", "ת�����");
  set ("long", @LONG
�������ת����ȡ��������ƽʱ���еĵط���
LONG);

  set("objects", ([ /* sizeof() == 2 */
  "/u/yekai/zspfm/ts.c" : 1,
  "/u/yekai/zspfm/swk.c" : 1,
  "/u/yekai/zspfm/zbj.c" : 1,
  "/u/yekai/zspfm/shs.c" : 1,
  "/u/yekai/zspfm/xbl.c" : 1,
  ]));
set("outdoors", 1);
set("no_fight", 1);
set("no_magic", 1);
  set("exits", ([ /* sizeof() == 2 */
"down" : "/d/city/paimaiwu.c",
]));

  setup();
}


