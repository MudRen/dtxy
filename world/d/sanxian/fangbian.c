#include <room.h>
inherit ROOM;
void create()
{
        set("short", "����֮��");
        set("long", @LONG
������Ƿ���֮������һ�������ķ�ӣ�ɢ���Ŷ��ĵ�ζ����
LONG
  );
  set("exits",([
        "northwest" : __DIR__"guodao",
      ]));  
   set("objects", ([
      
     ]) );  
        set("no_magic",1);
        create_door("northwest", "ľ��", "southeast", DOOR_CLOSED);
        setup();
} 

void init()
{
   add_action("do_search", "search");
   add_action("do_look", "look");
   add_action("getting", "zuan");
}

int do_look(string arg)
{
   object me;

   me = this_player();
   if (!arg || (arg != "���" && arg != "cesspit"))
      return 0;
   if(me->query_temp("marks/foundcesspit"))
      tell_object(me, "һ����ӣ�����̫�ɾ��˵㡣�϶��йŹ֣���Ȼ�и�С��(hole)������\n");
        me->set_temp("marks/foundhole", 1);
   return 1;
}

int do_search(string arg)
{
   object me;
   int llvl;

   me = this_player();
   llvl = (int)me->query("kar");
   if (!arg) {
      if(random(100) < llvl) {
         tell_object(me, "�㷢�ַ��(cesspit)����Щ��ʯ������ϸ������\n");
         me->set_temp("marks/foundcesspit", 1);
         return 1;
      }
      message_vision("$N��ס���ӣ�����ס���ģ����ĵز鿴�ŷ�ӡ�������\n", me);
      tell_object(me, "��ô���ĵط�����������̫���ˣ�����\n");
      return 1;
   }
   return 0;
}



int getting(string arg)
{
        object obj;
        object me;
                
        if(!arg || arg=="")
        {
                write("��Ҫ��ʲô��\n");
                return 1;
        }
        if( arg == "��" || arg == "hole" || arg == "С��")
        {
        me = this_player();
        if(me->query_temp("marks/foundhole")){
        message_vision("$N��ס���ӣ��������ӣ��ӷ�����С�����˽�ȥ��\n", me);
        me->start_busy(2);
        call_out("zuaning",2,me);
        me->stop_busy();
        message("vision","����һ�Σ������һ��С����"+me->name() + "�Ͻ����˳�����\n", environment(me),me);
        return 1;
        }
        }

        else
        {
                write("��"+arg+"��ɶ����ģ���Ϊ�������󰡣�\n");
                return 1;
        }

}
int zuaning(object me)
{
        if( !me->is_ghost()) {
        me->move(__DIR__"xiaodao");
        message_vision("����һ�Σ������һ��С����$N�Ͻ����˳�����\n", me);
        }
        return 1;
}
