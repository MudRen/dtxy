
// 离火三重
// yangwl 1/10/2001  可以加上门派限制

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,str;
        int extra;
        int ap,dp,chance;
        object weapon;
        extra = me->query_skill("huoyun-qiang",1);
        
        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "spear")
                        return notify_fail("你使用的武器不对。\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
               return notify_fail(HIR"「离火三重」"NOR"只能对战斗中的对手使用。\n");
        weapon = me->query_temp("weapon");
        if(extra < 180)
            return notify_fail("你的火云枪法还不够纯熟！\n");
     if(!wizardp(me) && me->query("family/family_name")!="火云洞")
           return notify_fail("“离火三重”只有火云洞门人才可以用！\n");
     if(target->is_busy())
           return notify_fail("对方已经够忙的了，就别吓唬人家了！\n");
        if(me->query("max_force") < 1500)
            return notify_fail("你的内力还不够，不要勉强了！\n"); 
        if(me->query("force") < 1200)
            return notify_fail("你的真气不够，不要勉强了！\n"); 
              
        
        //if(extra >= 400)  extra = 400;
        me->add("force", -extra/2);
        me->add_temp("apply/attack",extra/8);
        me->add_temp("apply/damage",extra/8);
        message_vision(HIR"\n$N手中前指的枪尖突然像着火一般，“砰”地炸出一团紫红色的火焰，绕
着通红透亮的枪身燃烧起来！！“刷”地拉出一道火红中映着紫焰的流光，
哗啦啦地就是一片遮天的火舌，往$n的头上盖去！"NOR,me,target);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        message_vision(HIR  "$N全身真气外放，衣衫冉冉飘动，双眸倏转妖红！！" NOR,me,target);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
				message_vision(HIR  "$N手中"+weapon->query("name")+ HIR"内所有阳气已是内燃敛收，放出肉眼难以直视的青白光华！" NOR,me,target);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        me->add_temp("apply/attack",-extra/8);
        me->add_temp("apply/damage",-extra/8);
        if( me->query("lunhui_zhuanshi") > 3 )
        	me->start_busy(1);
        else
        	me->start_busy(2);
        message_vision(HIR"$N手中"+weapon->query("name")+ HIR"一挥，一条火龙冲天而起！\n" NOR,me,target);
        message_vision(HIR"正是：吐雾遮三界,喷云照四方,一天杀气凶声吼,日月星辰不见光！\n"NOR,me,target);
        		  ap = me->query("combat_exp")/1000;
			  dp = target->query("combat_exp")/1000*5/4;
			  if (dp < 1) 
			   		dp = 1;
			  chance = (int)(random(ap + dp) * 100 / dp);
			  if( chance > 55 ) 
   			  {
						message_vision(HIB"$n何曾见过如此场面，立时被吓得动弹不得！\n" NOR,me,target);
						target->start_busy(3+random(3));
				}
				else if( chance > 33 ) 
				{
						message_vision(HIY"$n心神坚定，竟对翻腾飞舞的火龙视而不见！\n" NOR,me,target);
				}
				else
				{
						message_vision(HIC"$n一声冷笑，大喝：孽障还不束手就擒！\n" NOR,me,target);
						message_vision(HIC"紧接着$n全力攻出一招，竟将火龙打的灰飞烟灭！\n" NOR,me,target);
						COMBAT_D->do_attack(target, me, target->query_temp("weapon"));
						if (me->query("eff_kee")<0 || (!living(me) && me->query("kee")<0))  
                       {str=me->name()+HIM"被自己放出的"NOR+HIR"「火龙」"+HIM"烧死了，据说一点残渣都没剩下！";
	                 message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	               }
				}
				 if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
                       {str=target->name()+HIM"被"+me->name()+"放出的"NOR+HIR"「火龙」"+HIM"烧死了，据说一点残渣都没剩下！";
	                 message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	               }
        return 1;
}
