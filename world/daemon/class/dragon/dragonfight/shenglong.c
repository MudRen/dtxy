#include <ansi.h>
inherit SSERVER;
void npc_attack(object invoker, object target, string npc, object where);
void check(object me,object target,string name,int i);
string npc_dir = "/obj/npc/long";

int perform(object me, object target)
{
   string msg;
   object where,weapon;
   object soldier;
   int i,j, skill, wx, jj;
   string npc;
   object attacker,invoker;
   int cd = 6;
   if( !target ) target = offensive_target(me);

   if( !target
   ||   !target->is_character()
   ||   target->is_corpse()
   ||   target==me)
     return notify_fail("你对谁施展庐山升龙霸？\n");
      if (!target->is_fighting(me))             return notify_fail("只有在战斗中才可以使用「庐山升龙霸」！\n");
             
   if(!wizardp(me)&&(string)me->query("family/family_name") != "东海龙宫" )
        return notify_fail("你又不是东海弟子，不会庐山升龙霸。\n");
   if((int)me->query_skill("dragonfight", 1) < 50)
         return notify_fail("你的龙形搏击修为不深，施展不出庐山升龙霸。\n");
   
   if( me->query("lunhui_zhuanshi") )
   	cd = 5;
   if( time()-(int)me->query_temp("ba_end") < cd )
                return notify_fail("你刚用过「庐山升龙霸」,内息还无法调整！\n");
   if((int)me->query("force") < 1200 )
     return notify_fail("你的内力不够。\n");

   if((int)me->query("sen") < 100 )
     return notify_fail("你现在神智不清！\n");

   me->receive_damage("sen", 100);
   me->delete("env/brief_message");
   target->delete("env/brief_message");
   weapon=me->query_temp("weapon");
   message_vision(HIB"$N默运碧海神通，身法一展，竟然使出"HIC"「庐山升龙霸」"HIB"舍身扑向$n！\n"NOR,me,target);
   COMBAT_D->do_attack(me, target, weapon);
   COMBAT_D->do_attack(me, target, weapon);
   COMBAT_D->do_attack(me, target, weapon);
   i=(int)me->query_skill("dragonfight", 1)-100; 
   i/=50;
   me->add("force", -(200+i*30));
   if (i>9) i=9;
   if (i > 0)
   {
   	msg = HIC "$N大喝一声『升龙』，"+chinese_number(i)+"条神龙自九天而起，直飞$n！\n\n" NOR;  
        message_vision(msg, me, target);
   }
   //where=environment(target);
   invoker =  me;
   skill = me->query_skill("unarmed", 1);
   wx = me->query("combat_exp");
   for(j=1;j<=i;j++)
   {
   	//call_out("npc_attack", 1, me, target, npc_dir+j, where);
   	seteuid(getuid());
   	if( me->query("lunhui_zhuanshi") > 4 )
   	{
   		jj = j + 10;
   		npc = npc_dir+jj;
   		attacker = new(npc);
   		attacker->init_data(skill, wx);
   	}
   	else
   	{
   		npc = npc_dir+j;
   		attacker = new(npc);
   	}
   	attacker->move(environment(invoker));
   	COMBAT_D->do_attack(attacker, target, attacker->query_temp("weapon"));
   	if(target->query_temp("last_damage_from")==attacker)
       	target->set_temp("last_damage_from", invoker);
   	if(target->query_temp("last_fainted_from")==attacker)
       	target->set_temp("last_fainted_from", invoker->query("id"));
   	destruct(attacker);
   }
   //call_out("check", 2, me, target,target->name(),i);
   	if ( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
	{
		if( i < 1 )
			msg=HIM+me->name()+"竟然使出了东海秘传的"NOR+HIC"「庐山升龙霸」"+HIM"，看来又有人死在这种霸道的拳术之下。";
		else
        		msg=HIM+me->name()+"使出东海秘传"NOR+HIC"「庐山升龙霸」"+HIM"，自九天之上引来"+HIY+ chinese_number(i) +HIM"条神龙将"+target->name()+HIM"当场击杀！";
        	message("channel:rumor",HIM"【空穴来风】某人："+msg+"\n"NOR,users());
	}
   me->start_busy(2+random(1));
   me->set_temp("ba_end",time());
   return 1;
}

void npc_attack(object invoker, object target, string npc, object where)
{
   object attacker;
   string msg,str;
   if(!invoker || !target) return;
   if( environment(invoker) != environment(target) ) return;
   if( environment(target) != where) return;
   seteuid(getuid());
   attacker = new(npc);
   attacker->move(environment(invoker));
   COMBAT_D->do_attack(attacker, target, attacker->query_temp("weapon"));
   if(target->query_temp("last_damage_from")==attacker)
       target->set_temp("last_damage_from", invoker);
   if(target->query_temp("last_fainted_from")==attacker)
       target->set_temp("last_fainted_from", invoker->query("id"));
   destruct(attacker);
}
void check(object me,object target,string name,int i)
{
	string msg;
	if( !objectp(me) )
		return;
	if( !objectp(target) )
	{
		if( i < 1 )
			msg=HIM+me->name()+"竟然使出了东海秘传的"NOR+HIC"「庐山升龙霸」"+HIM"，看来又有人死在这种霸道的拳术之下。";
		else
        		msg=HIM+me->name()+"使出东海秘传"NOR+HIC"「庐山升龙霸」"+HIM"，自九天之上引来"+HIY+ chinese_number(i) +HIM"条神龙将"+ name +HIM"当场击杀！";
        	message("channel:rumor",HIM"【空穴来风】某人："+msg+"\n"NOR,users());
	}
	else if (target->query("eff_kee")<0 || !living(target))  
	{
		if( i < 1 )
			msg=HIM+me->name()+"竟然使出了东海秘传的"NOR+HIC"「庐山升龙霸」"+HIM"，看来又有人死在这种霸道的拳术之下。";
		else
        		msg=HIM+me->name()+"使出东海秘传"NOR+HIC"「庐山升龙霸」"+HIM"，自九天之上引来"+HIY+ chinese_number(i) +HIM"条神龙将"+target->name()+HIM"当场击杀！";
        	message("channel:rumor",HIM"【空穴来风】某人："+msg+"\n"NOR,users());
	}
	return;
}

