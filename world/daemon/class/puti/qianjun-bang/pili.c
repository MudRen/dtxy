#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	int kar,tkar;
        object weapon = me->query_temp("weapon");
      	string msg,str; 
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「霹雳流星」？\n");
       if  ((string)me->query("family/family_name") != "方寸山三星洞" )
                       return notify_fail("你的千均棒法似乎并非方寸山真传。\n");  
        if(!me->is_fighting(target))
                return notify_fail("「霹雳流星」只能在战斗中使用！\n");

        if((int)me->query("max_force") < 500 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 300 )
                return notify_fail("你的精神不足，没法子施用外功！\n");
        if((int)me->query_skill("qianjun-bang",1) < 50)
                return notify_fail("你的千钧棒级别还不够，使用这一招会有困难！\n");

	//if( time()-(int)me->query_temp("xiao_end") < 10 )
	//return notify_fail("绝招用多就不灵了！\n");

        me->delete("env/brief_message");
        target->delete("env/brief_message");
	me->add("force", -100);
	kar=me->query_skill("qianjun-bang",1);
	message_vision(HIC"\n$N运足精神，身形一转，霹雳间连续向$n攻出了三招！\n"NOR,me,target);
        me->add_temp("apply/damage",kar/5);
	me->add_temp("apply/attack",kar);
        me->set_temp("QJB_perform", 4);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        me->set_temp("QJB_perform", 1);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        me->set_temp("QJB_perform", 6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(HIC"\n$N发现三招之后，体力尚且充沛，又打出一招。\n"NOR,me,target);
        me->set_temp("QJB_perform",8);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),0);
        me->delete_temp("QJB_perform");
        tkar=target->query("force_factor");
        if(random(kar+tkar)>tkar) 
        {
        	message_vision(HIR"\n$N打疯了似的,竟然还不住手,手中"+weapon->name()+HIR"得势不饶人地进攻。\n"NOR,me,target);
                target->receive_damage("kee", me->query_skill("stick")/3);
                target->receive_wound("kee", me->query_skill("stick")/6);
                COMBAT_D->report_status(target);
        }
        if( me->query("lunhui_zhuanshi") > 1 )
		me->start_busy(1);
	else
		me->start_busy(2);
        if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
 	{ 
 		str=me->name()+"一招"+NOR+HIG"「霹雳流星」"+NOR+HIM"把"+target->name()+NOR+HIM"活活打死，尸体上伤痕累累，惨不忍睹！";
                message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
        me->add_temp("apply/damage",-kar/5);
  	me->add_temp("apply/attack",-kar);
        me->receive_damage("sen", 100);
        //remove_call_out("perform2");
        //call_out("perform2",2, me, target);
        //message_vision(HIC"\n$N积蓄力量准备进行下一次攻击！\n"NOR,me,target);  
        //me->set_temp("xiao_end",time());
        return 1;
}

int perform2(object me, object target)
{
        int kar,tkar;
      	string msg,str; 
        string wep;
        if (!me) return 1;
        if(!target) return 1;
        if(!me->is_fighting(target)) return 1;
        if(environment(me) != environment(target)) return 1;
        if(!living(target)) return notify_fail("对手已经不能再战斗了。\n");
        if(!objectp(wep = me->query_temp("weapon")) || wep->query("skill_type") != "stick"){
        if(!wep)message_vision(HIY"$N手中武器已失，使不出剩下的功夫了，$n不禁松了口气．\n"NOR,me,target);
        else  message_vision(HIY"$N亮出"+wep->name()+HIY"而停止追击，$n不禁松了口气．\n"NOR,me,target);
        return 1;}
        //remove_call_out("remove_effect");
        //call_out("remove_effect", random(5)+2, me);
        kar=me->query("force_factor");
        tkar=target->query("force_factor");
        message_vision(HIC"\n$N发现数招之后，体力尚且充沛，又打出一招。\n"NOR,me,target);
        if(random(kar+tkar)>tkar) 
        {
              target->start_busy(random(2));
              me->set_temp("QJB_perform",8);
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"),0);
              me->add("force", -100);
              me->delete_temp("QJB_perform");
       }
       if((me->query("combat_exp")/20000+me->query_skill("stick")+me->query_skill("qianjun-bang"))
             >random(target->query("combat_exp")/20000+target->query_skill("dodge")))
        {       
		if(environment(me)!=environment(target))
            		return 1;
                message_vision(HIR"\n$N打疯了似的,竟然还不住手,"+wep->name()+"得势不饶人地进攻。\n"NOR,me,target);
                target->receive_damage("kee", me->query_skill("stick")/3);
                target->receive_wound("kee", me->query_skill("stick")/6);
                COMBAT_D->report_status(target);
        if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
 { str=me->name()+"一招"+NOR+HIG"「霹雳流星」"+NOR+HIM"把"+target->name()+NOR+HIM"活活打死，尸体上伤痕累累，惨不忍睹！";
                      message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
                    }
                me->add("force",-200);
           }
}
