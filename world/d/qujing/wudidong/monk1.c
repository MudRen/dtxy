#include <ansi.h>

//inherit ROOM;
inherit "/d/city/misc/scoresheet.c";
#include </d/city/misc/banned.h>


void create ()
{
  restore();
  set ("short", "����");
  set ("long", @LONG
����ȼ��յ��С���͵ƣ�΢���Ļƹ���ֻ�����ϵĸɲݶ������Ÿ���
���У��������ã�ȫ��Ѫ���߰ߣ��ѱ���ĥ�ò��������ˣ���ϲ��û
��������͡�

LONG);
  set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"jail",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/fangzhang-jail" : 1,
]));
  set("outdoors", 0);
  setup();
}

void init() {
  add_action("do_quit",banned_action);
}

int do_quit(string arg) {
  write("�㲻�����������������\n");
  if (wizardp(this_player())) write("��ʦ�����ͬһ·���ڵ�banned.h�ĵ���\n");
  return 1;
}

