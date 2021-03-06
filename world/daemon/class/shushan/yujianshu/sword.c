/*	
	剑心，蜀山解密7种随机，镇妖塔7个剑柱
	
	看剑念奴娇
	练剑忆江南
	负剑少年游
	挥剑满江红
	藏剑长相思
	封剑一剪梅
	掷剑踏莎行
	
	《相见欢》：
　　　　“罗襦绣袂香红，画堂中！”
　　　　	舞动树枝，剑势如虹，晃如破天。
　　　　“细草平沙番马，小屏风！”
　　　　	牵引剑气，化成清风而扶。
　　　　“卷罗幕，凭汝阁，思无穷！”
	　　　　清风静止而立，化为一幕屏风，却又变化无穷。
　　　　“暮雨轻烟魂断--”
　　　　	屏风化为丝丝轻雨而散，散后而聚。
　　　　“隔断栊！”
		《相见欢》最后一式把聚集在一起的气息如爆裂般炸开。
	
*/
#include <ansi.h>
inherit SSERVER;

int perform(object me, object target)
{
  object weapon;
  int damage,enhance;   
  string msg,str;
  int i;
  int cd = 10;
  if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「剑心」？\n");
        if(!wizardp(me) && me->query("family/family_name") != "蜀山派")
                return notify_fail(HIC"「剑心」"+NOR"是蜀山不传之密！\n");
        if(!me->is_fighting(target))
                return notify_fail("「剑心」只能在战斗中使用！\n");
        if((int)me->query("force") < 1500 )
                return notify_fail("你的内力不够！\n");
        if ( !me->query("sword_known") ) //暂时分为2个阶段 1,2
           return notify_fail("你没有口诀，无法领悟到「剑心」的奥秘！\n");
        if((int)me->query("kee") < 600 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if( time()-(int)me->query_temp("sword_end") < cd )
          return notify_fail("你现在内息紊乱，无法使用「剑心」！\n");
        if(me->query_skill("sword", 1) < 200 || me->query_skill("yujianshu", 1) < 200)
                return notify_fail("你的剑法级别还不够，使用这一招会有困难！\n");
        if(me->query_skill("force", 1) < 200 || me->query_skill("zixia-shengong", 1) < 200)
                return notify_fail("你的内功级别还不够，使用这一招会有困难！\n");

    	weapon=me->query_temp("weapon");
    	enhance=me->query_skill("zixia-shengong",1);
	damage=me->query_skill("yujianshu",1);
	i = me->query("sword_known");
	damage = damage + damage/(10-i);
	//if( i > 3 )
  //  	{
	    	target->start_busy(1);
	//}
	i = 1 + random(i);
  
	message_vision(HIC"\n$N不顾$n的攻击，闭上双眼默默体会"+weapon->name()+HIC"中的灵动之波。\n"NOR,me,target);
	message_vision(HIC"\n$N缓缓睁开双眼，眼中透漏出的精光，竟让$n无法正视。\n"NOR,me,target);
	me->set_temp("sword_type", i);
	switch(i)
	{
		case 1:
     		{	
     			str=me->name()+"使出蜀山剑法绝学「"HIY"剑心"HIM"－"HIC"念奴娇"HIM"」，"+target->name()+NOR+HIM"被看剑之技送下了黄泉！";
			message_vision(HIC"\n$N感念到刚刚接触"+HIY"剑"+HIC"时的兴奋与豪情。\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"应念发出夺目亮光，直指$n。\n"NOR,me,target);
     			break;
     		}
     		case 2:
     		{	
     			str=me->name()+"使出蜀山剑法绝学「"HIY"剑心"HIM"－"HIG"忆江南"HIM"」，"+target->name()+NOR+HIM"被炼剑之技送下了黄泉！";
			message_vision(HIC"\n$N感念到刚刚开始练"+HIY"剑"+HIC"时的欣喜。\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"应念发出欢快的颤音。\n"NOR,me,target);
     			break;
     		}
     		case 3:
     		{	
     			str=me->name()+"使出蜀山剑法绝学「"HIY"剑心"HIM"－"HIC"少年游"HIM"」，"+target->name()+NOR+HIM"被负剑之技送下了黄泉！";
			message_vision(HIC"\n$N感念到第一次负"+HIY"剑"+HIC"出游时的畅快。\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"应念轻轻震动。\n"NOR,me,target);
     			break;
     		}
     		case 4:
     		{	
     			str=me->name()+"使出蜀山剑法绝学「"HIY"剑心"HIM"－"HIR"满江红"HIM"」，"+target->name()+NOR+HIM"被挥剑之技送下了黄泉！";
			message_vision(HIC"\n$N感念到路见不平，拔"+HIY"剑"+HIC"相助时的胸中正气。\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"应念生出三寸剑芒。\n"NOR,me,target);
     			break;
     		}
     		case 5:
     		{	
     			str=me->name()+"使出蜀山剑法绝学「"HIY"剑心"HIM"－"HIM"长相思"HIM"」，"+target->name()+NOR+HIM"被藏剑之技送下了黄泉！";
			message_vision(HIC"\n$N灵念突现，将"+HIY"剑"+HIC"道隐于意念之中。\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"应念消失不见，$N却散发出凌厉的剑气。\n"NOR,me,target);
     			break;
     		}
     		case 6:
     		{	
     			str=me->name()+"使出蜀山剑法绝学「"HIY"剑心"HIM"－"HIW"一剪梅"HIM"」，"+target->name()+NOR+HIM"被封剑之技送下了黄泉！";
			message_vision(HIC"\n$N灵念突现，以意化"+HIY"剑"+HIC"。\n"NOR,me,target);
			message_vision(HIC"\n$N突然失去踪影，$n仅能感觉到无边无际的剑气。\n"NOR,me,target);
     			break;
     		}
     		case 7:
     		{	
     			str=me->name()+"使出蜀山剑法绝学「"HIY"剑心"HIM"－"HIC"踏莎行"HIM"」，"+target->name()+NOR+HIM"被掷剑之技送下了黄泉！";
			message_vision(HIC"\n$N与"+HIY"剑灵"+HIC"心念相通，以气御剑。\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"应念脱手飞出。\n"NOR,me,target);
     			break;
     		}
     		case 8:
     		{
     			str=me->name()+"使出蜀山剑法绝学「"+NOR+HIY"剑心"HIM"－"BLINK+HIR"相见欢"NOR+HIM"」，"+target->name()+NOR+HIM"被烟雨般的剑气送下了黄泉！";
			message_vision(HIC"\n"+weapon->name()+HIC"发出剑鸣之声，仿若一时之间活了过来。\n"NOR,me,target);
			message_vision(HIC"\n"+weapon->name()+HIC"如蜿蜒奔流，发出点点波光闪动，将$n重重围住。\n"NOR,me,target);
     			break;
     		}
	}
	target->add_temp("apply/dodge",-enhance/2);
        target->add_temp("apply/parry",-damage/2);
        me->add_temp("apply/attack",enhance/2);
    	me->add_temp("apply/damage",damage/2);
    	me->set_temp("pfm_xjh", 0);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("pfm_xjh", 1);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("pfm_xjh", 2);
    	COMBAT_D->do_attack(me, target, weapon);
    	me->set_temp("pfm_xjh", 3);
    	COMBAT_D->do_attack(me, target, weapon);
	me->set_temp("pfm_xjh", 4);
    	COMBAT_D->do_attack(me, target, weapon);
    	
    	if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
      	{ 
        	message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
       	}
       	me->delete_temp("sword_type");
	me->delete_temp("pfm_xjh");
    	me->add("force", -300);
	me->start_busy(2);
	target->add_temp("apply/dodge",enhance/2);
        target->add_temp("apply/parry",damage/2);
        me->add_temp("apply/attack",-enhance/2);
    	me->add_temp("apply/damage",-damage/2);
    	me->set_temp("sword_end",time());	
    	
  return 1;
}
