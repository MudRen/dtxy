#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "ʯ��");
  set ("long", @LONG

ʯ��������ƽ̹����ɨ��Ҳʮ�ָɾ���û��ʲô�����������
���ڴ��߶����±���һʯ���������ĸ�ʯ�ʡ�������һС�ݣ���
ǰʯ���Ͽ��С�ľ���֡����֡�
LONG);

  set("objects", ([ /* sizeof() == 1*/ 
//  __DIR__"npc/hunter" : 2,
]));
  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
  "northdown" : __DIR__"ping",
  "southwest": __DIR__"huilin",
  "southeast": __DIR__"bolin",
  "south" : __DIR__"xinglin",
]));

  setup();
}

void init()
{ 
 	add_action("do_dig","dig");
}

int do_dig(string arg)
{
        object obj;
        object me;
        object arrow;
        me = this_player();
        obj = me->query_temp("weapon");
        if( me->query_temp("jueqing/houyi") != 2 )
        {
        	return 0;	
        }
        if( !obj )
        {
        	write("������֣���ô�ڣ�\n");
        	return 1;
        }
        if( present("jiutian arrow",me) )
        {
        	write("���Ѿ��ڵ��˰�����\n");
        	return 1;
        }
        message_vision(sprintf("$N�����е�%sʹ����ʯ�����ھ�\n",obj->name()),me);
        if( random(me->query("kar")) > 20 )
        {
        	message_vision("$N���ú��������˽����Ķ��������������\n",me);
        	message_vision("$N�ӰѾ��������ڳ���һ����������������ȥ����ûʲô�ر�ģ�\n",me);
        	arrow = new("/d/moon/obj/jiutian-arrow");
        	arrow->move(me);
        }
        return 1;
}