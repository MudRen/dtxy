// edited by mind
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
��Ѩ��Χ������ߣ���Ȼû�п��Բ���һ���˵ĵط���
��ֵ��ǣ���Ȼ��һ�ɵ����ĺ��ռ�������������
LONG
  );
   set("objects", ([
      
   ]) );  
        set("no_magic",1);
        
        setup();
} 
void init()
{
   add_action("do_smell", "smell");
   add_action("do_step", "step");
}

int do_step(string arg)
{
   object me, room;
   me = this_player();

   if(me->query_temp("marks/smell")) {
      tell_object(me, "��һ��̤��������ӡ���ϣ���վ�ĵط���ͻȻ�����������ȥ��\n\n");
      message("vision", "�����һ������"+me->name(me)+"��ͻȻ������ȥ�������ˡ�\n", environment(me),me );
      room = find_object(__DIR__"tongzi1");
      if(!objectp(room)) room=load_object(__DIR__"tongzi1");
      me->move(room);
      return 1;
   }
   return 0;
}

int do_smell(string arg)
{
   object me, room;
   me = this_player();

   tell_object(me,HIY"���ռ������������������������ޣ������Ʊ��ӣ���ϸ���ţ����������Ǵ����档����\n"NOR);
   message("vision",me->name(me)+"����¶���Źֵ����飬�ƺ�������ʲô��\n", environment(me),me);
   tell_object(me, "\n��Ͻ���ͷһ���������и���ֵ������Ե�ӡ��(step)������ϸ�ң�������������\n", me);
   me->set_temp("marks/smell", 1);      

   return 1;
}

