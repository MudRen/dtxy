inherit ITEM;

#include <ansi.h>


int do_he(string);

void create() 
  {
   set_name(YEL "五仙汤" NOR,({"tang"}));
   set("long","一碗花花绿绿的"+this_object()->query("name")+"，尝尝(he)味道？\n");
   set_weight(50);
   set("unit","碗");
   setup();
  }

void init()
{
  add_action("do_he", "he");
}

int do_he(string arg)
  {
   object me=this_object();
   object who=this_player();
   if( !this_object()->id(arg) ) return notify_fail("你想喝啥？\n");
   message_vision("$N端起"+me->query("name")+"咕嘟咕嘟的喝了下去。\n", who);
   if ( me->query("prices")<= 0 )  message_vision("但什么滋味也没尝出来。\n", who);
   else if( who->query("piaoxue/handu") == 1 )
   {
   	message_vision("$N苦得涕泪横流，强忍着没吐出来。\n", who);
      	who->improve_skill("ningxie-force", me->query("prices"));
      	tell_object(who,"你运转凝血神功，小心翼翼的对抗着毒汤的药力。\n");
      	tell_object(who,"你对凝血神功的理解加深了。\n");
      	who->set("piaoxue/handu",2);
      	tell_object(who, YEL "你的冰谷凝血功增加了"
        	 +chinese_number(me->query("prices"))+"点！\n" NOR);
        who->unconcious();
   }
   else if( who->query("piaoxue/handu") == 2 )
   {
   	message_vision("$N苦得涕泪横流，强忍着没吐出来。\n", who);
      	who->improve_skill("ningxie-force", me->query("prices"));
      	tell_object(who,"你运转凝血神功，小心翼翼的对抗着毒汤的药力。\n");
      	tell_object(who,"你对凝血神功的理解加深了。\n");
      	tell_object(who, YEL "你的冰谷凝血功增加了"
         	+chinese_number(me->query("prices"))+"点！\n" NOR);
        who->delete("piaoxue");
        if( random(who->query("int")+who->query("con")) > 20 - random( who->query("lunhui_zhuanshi") ) )
        {
        	who->set("piaoxue_known",1);
        	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗大鹏明王(dapeng mingwang)：" + who->name() + "勇气过人，凭内力对抗毒素，从此以后不再惧怕寒毒了！\n\n\n"NOR,users());
        }
        else
        {
        	who->set("piaoxue_cant",1);
        	message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗大鹏明王(dapeng mingwang)：" + who->name() + "勇气过人，凭内力对抗毒素，可惜未能悟得正确功法，也无法学习大雪山更高深得武功了！\n\n\n"NOR,users());
        }
        who->unconcious();
   }
   else if ( (int)who->query_skill("ningxie-force", 1) < 10 
   || (int)who->query_skill("ningxie-force", 1) > 199  )  
     {
      message_vision("$N只感到一阵恶心，天悬地转。\n", who);
      who->unconcious();
     }
   else 
     {
      message_vision("$N苦得涕泪横流，强忍着没吐出来。\n", who);
      who->improve_skill("ningxie-force", me->query("prices"));
      tell_object(who,"你只感到腹内如有数十把小刀在乱攒乱刺，你使尽了力气，"
         +"才将毒汤的药力完全化解。\n");
      tell_object(who, YEL "你的冰谷凝血功增加了"
         +chinese_number(me->query("prices"))+"点！\n" NOR);
     } 
   destruct(me);
   return 1;
  }

