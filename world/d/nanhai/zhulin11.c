// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// Room: /d/nanhai/zhulin.c

#include <ansi.h>

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
  "north" : __DIR__"zhulin"+sprintf("%d", random(25)),
  "west" : __DIR__"zhulin"+sprintf("%d", random(25)),
  "south" : __DIR__"zhulin"+sprintf("%d", random(25)),
  "east" : __DIR__"zhulin"+sprintf("%d", random(25)),
]));

   setup();
//   replace_program(ROOM);
}

void init()
{

        object me=this_player();

        if ( (me->query_temp("aware_of_jinguzhou")) && 
     (me -> query_kar() > 20) ) {
                tell_object(me, HIY"������һ�����ƺ���������\n"NOR);
        }
        add_action("do_search", "search");
}

int do_search (string arg)
{
  object ob, me = this_player();

    if (!arg || arg != "jinguzhou")
  {
    message_vision ("$N����ȥѰ��ʲô��\n",me);
    return 1;
  }

  if (me -> query_kar() < 20)
  {
    message_vision ("$N����ȥ���������ҷ���������\n",me);
    return 1;
  }

   if( !(ob = find_object(__DIR__"obj/jingu1")) ) {
            ob = load_object(__DIR__"obj/jingu1");
       ob -> move(me);
       message_vision ("$N�۾�һ���������䣡\n",me);
       if (me->query_temp("aware_of_jinguzhou"))
     me -> delete_temp("aware_of_jinguzhou");
       return 1;   
   }

   message_vision ("$N����ȥ���������ϸ�ط�����ȥ��\n",me);
   return 1;
}

