// create by snowcat.c 12/8/1997
// edit by canoe ���޸�ûȡ�꾭�Ĳ��ܽ�ȥ

inherit ROOM;
#include <obstacle.h>

void create ()
{
  set ("short", "����");
  set ("long", @LONG

�������㰸������ÿ���㰸���н�����¯��ֻ��������������
�����ƣ�����һ������ؽ����ơ�������һ����ͨ����۱�
�¥��Ϊ����ؾ�����

LONG);

  set("exits", ([
        "up"   : __DIR__"baoge2",
        "west"   : __DIR__"daxiong",
  "1"   : __DIR__"chanfang1",
 "2"   : __DIR__"chanfang2",
 "3"   : __DIR__"chanfang3",
"4"    : __DIR__"chanfang4",
 "5"    : __DIR__"chanfang5",
              ]));
  set("objects", ([
        __DIR__"npc/randeng" : 1,
        __DIR__"npc/xiantong" : 2,
     ]));

  setup();
}

int valid_leave(object who, string dir)
{
        if(dir=="west"||dir=="up")
         	return ::valid_leave(who, dir);
        else 
        {
        if (who->query("obstacle/number") < sizeof(obstacles) && !wizardp(who))
        return notify_fail("ȼ�ƹŷ������㣺�������޵�֮������֮�أ�������ţ�\n");
        else 
              return ::valid_leave(who, dir);
        }
}

