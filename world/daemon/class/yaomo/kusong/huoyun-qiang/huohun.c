//火魂
//requirement:huomoforce,huoyun-qiang all over 60

#include <ansi.h>
 
inherit F_DBASE;
inherit SSERVER;
 
void remove_effect(object me, object target, int amount);
 
int perform(object me, object target)
{
        int skill_spear, skill_force, str_amount,spear_amount, delay;
        object weapon;
        if(me->query("family/family_name")!="火云洞")
		return notify_fail("「火魂」只有火云洞门人才可以用！\n");
	if( !me->query("huohun_known") )
		return notify_fail("你还没有学会「火魂」。\n");	
	if( time() - me->query_temp("huohun_end") < 10 )
		return notify_fail("你的体力不足，使用「火魂」会有危险。\n");	
        if (me->query_skill_mapped("force")!="huomoforce")
        	return notify_fail("「火魂」必须配合火魔心法才能使用。\n");
        skill_force=me->query_skill("huomoforce",1);        
        if (skill_force<200) return notify_fail("你的火魔心法不够纯熟。\n");
        skill_spear=me->query_skill("huoyun-qiang",1);
        if (skill_spear<200) 
           return notify_fail("你的枪法太差劲了。\n"); 
        if( (int)me->query("force") < skill_force + 500 )      
                return notify_fail("你的内力不够。\n");
        if( (int)me->query("kee") < skill_spear + 500 )      
                return notify_fail("你的气血不够。\n");
        if( (int)me->query_temp("shenli") )
                return notify_fail("你已经在运功中了。\n");
        weapon = me->query_temp("weapon");
        me->add("force", -skill_force);
        me->receive_wound("kee",skill_spear);
        message_vision(HIR"\n$N咬破舌尖，向"+weapon->name()+HIR"喷出一道血雾。\n"NOR,me);
        message_vision(HIR"\n”嘭“的一声，"+weapon->name()+HIR"上燃起熊熊烈火，火焰像巨龙一样蜿蜒伸缩！\n"NOR, me);
 				
        spear_amount = skill_spear*(2+me->query("huohun_known"))/10;
        str_amount = skill_force*(2+me->query("huohun_known"))/10; 
        me->add_temp("apply/strength",str_amount);
        me->set_temp("apply/spear",spear_amount);
        me->set_temp("shenli", 1);
        delay = 15;
        if( me->query("lunhui_zhuanshi") > 4 )
        	delay = 30;
        me->start_call_out( (: call_other, __FILE__, "remove_effect", 
           me, str_amount,spear_amount:), delay);
         return 1;
}
 
void remove_effect(object me, int str_amount,int spear_amount)
{
        me->add_temp("apply/strength", -str_amount);
        me->delete_temp("apply/spear");
        me->delete_temp("shenli");
        me->set_temp("huohun_end",time());
        message_vision(HIR"$N感到体力不支，像火一样的巨龙消失了。\n"NOR,me);
}


