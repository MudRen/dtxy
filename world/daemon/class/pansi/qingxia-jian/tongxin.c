// tongxin.c 日月同芯
// 由紫霞、青霞同为灯芯所得
// daemon/skill/chixin-jian/
// by kryos,  huarong edit / 2003-03-06
 
#include <ansi.h>
 
inherit SSERVER;

int perform(object me)
{
        string msg,str; 
        object weapon, target;
        object ob;
        int skill, skill2,extra,damage;
	int cd = 7;
        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qingxia-jian",1);
        skill2 = me->query_skill("yinsuo-jinling",1);
	//if(!wizardp(me))
        //	return notify_fail("巫师正在测试"+HIW+"「日月同芯」"+NOR+"。。。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("笨蛋，不使剑怎么能使「日月同芯」？\n");

        if(me->query("family/family_name")!="盘丝洞")
                return notify_fail("不了解青霞与紫霞心事之人,如何能有此体会！\n");
                
        if( !me->is_fighting(target)|| !living(me) )
                return notify_fail("「日月同芯」只能在战斗中使用。\n");

//        if( me->query_temp("BAIFA_perform") ) 
//                return notify_fail("使用醉生梦死时不能分心他用。\n");

        if( (int)me->query("force") < 1000 )
                return notify_fail("你现在的内力不足！\n");
        
        if( (int)me->query("max_force") < 1500 )
                return notify_fail("你现在的内功太差！\n");
	if( me->query("lunhui_zhuanshi") > 3 )
		cd = 5;
	else if( me->query("lunhui_zhuanshi") )
		cd = 6;
        if( time()-(int)me->query_temp("xin_end") < cd )
                return notify_fail("绝招用多就不灵了！\n");

        if( skill < 150)
                return notify_fail("你连青霞仙子的武功都没有练好，怎么使用「日月同芯」! \n");

        if( skill2 < 150)
                return notify_fail("你连紫霞仙子的武功都没有练好，怎么使用「日月同芯」! \n");

        if( me->query_skill_mapped("sword") != "qingxia-jian") 
                return notify_fail("不配合青霞仙子的青霞剑法，如何使用「日月同芯」！\n");
                
        if( me->query_skill_mapped("whip") != "yinsuo-jinling") 
                return notify_fail("不配合紫霞仙子的银索金铃，如何使用「日月同芯」！\n");
        extra = skill + skill2;
        target->add_temp("apply/dodge",-extra/5);
        target->add_temp("apply/parry",-extra/5);
        me->add_temp("apply/attack",extra/5);
    	me->add_temp("apply/damage",extra/5);
        me->receive_damage("sen", 100);       
        message_vision(HIC"\n$N"+HIC+"默默念起紫霞和青霞仙子偶然提起的经文，$n"+HIC+"听$N"+HIC+"语音清脆，越念越是冲和安静，全身隐隐发出圣洁的光辉。\n\n"NOR+
               WHT"$n"+WHT+"只觉四周尽是梵音清唱，隐约间仿似失去了$N"+WHT+"的身形。\n "NOR, me,target);
       	message_vision(HIY"\n$N"+HIY+"身随意动，随手一剑刺向$n\n"NOR, me,target);
       	damage = COMBAT_D->do_attack(me, target, weapon);
	if (damage > 0)
        {
                message_vision(HIC"\n$n"+HIC+"发现$N"+HIC+"的身形渐渐变化,待擦目细看,眼前分明是一盏神灯，$N"+HIC+"飘然立在灯盏之上，随光而舞！\n"NOR,me,target);
                message_vision(HIY"\n$N"+HIY+"意随心动，随手一剑刺向$n\n"NOR, me,target);
                        damage = COMBAT_D->do_attack(me, target, weapon);
               	if (damage > 0 && skill > 199)
               	{
                       	message_vision(HIC"\n$n"+HIC+"只觉$N"+HIC+"的剑姿飘忽不定,却是精彩异常,待凝神观看，$N"+HIC+"却已不见，灯盏之上一青色火苗悄悄燃起！\n"NOR,me,target);
                        message_vision(HIY"\n$N"+HIY+"心随念动，随手一剑刺向$n\n"NOR, me,target);
                        damage = COMBAT_D->do_attack(me, target, weapon);
                        if (damage > 0 && skill > 249)
                        {
                               	message_vision(HIC"\n$n"+HIC+"凝视灯盏,竭尽心力寻找$N"+HIC+"的身形，却发现灯盏之上又燃起一紫色火苗！\n"NOR,me,target);  
                                message_vision(HIY"\n$N"+HIY+"念从虚生，随手一剑刺向$n\n"NOR, me,target);
                                damage = COMBAT_D->do_attack(me, target, weapon);
                                if (damage > 0 && skill > 299)
                                {
                                        message_vision(HIC"\n$n"+HIC+"心神为$N"+HIC+"所摄,不由自主随着两点灯火的聚散而舞！\n"NOR,me,target);
                                        message_vision(HIR"\n紫青灯火飘动之间有若高手攻防，$n"+HIR+"不自觉中模仿！\n"NOR,me,target);
                                        COMBAT_D->do_attack(target, target, target->query_temp("weapon"));
                                        target->set("last_damage_from", me);
                                       	message_vision(HIY"\n$N"+HIY+"心合天地，随手一剑刺向$n\n"NOR, me,target);    
					damage = COMBAT_D->do_attack(me, target, weapon);
                                       	if (damage > 0 && skill > 349)
                                        {
                                               	message_vision(HIC"\n$n"+HIC+"眼前所见，心中所想尽是紫青灯火。忽然间，两点灯火幻化衍生！\n"NOR,me,target);
                                               	message_vision(HIC"\n$n"+HIC+"恍然置身梦境，再仔细琢磨，眼前千万竟是$n"+HIC+"之前生今世！\n"NOR,me,target);
                                               	message_vision(HIY"\n$N"+HIY+"手中剑忽然发出日月之光，闪电般刺向$n\n"NOR, me,target);
                                               	message_vision(WHT"\n$n"+WHT+"只觉光芒刺目，却无力从梦中挣脱！\n"NOR, me,target);
                                                damage = COMBAT_D->do_attack(me, target, weapon);
                                                if (damage > 0)
                                                {
                                                       	message_vision(HIC"\n$n"+HIC+"已经万念俱灰...\n"NOR,me,target);
                                                        target->receive_damage("sen", damage, me);
                                                }
	                                        else 
	                                        {
	                                                message_vision(HIC"\n忽然一阵轻风吹过，紫青灯火不停闪烁，$n"+HIC+"恍然惊醒，已是大汗淋漓！\n"NOR,me,target); 
	                                                target->receive_damage("sen", 100, me);
	                                        }
	                              	}
					else
		                        {
		                        	message_vision(HIC"\n忽然灯火一顿，原来$N"+HIC+"想起前生今世，不由黯然神伤！\n"NOR,me,target);        
		                                message_vision(HIM"\n$N"+HIM+"顿悟心境，释然一笑，$n"+HIM+"不觉一怔，$N"+HIM+"借机挥剑急攻！\n"NOR,me,target);
		                                COMBAT_D->do_attack(me, target, weapon);
					}
				}
		                else
		                {
		                	message_vision(HIC"\n忽然青色灯火摇摆不定，竟似不愿与紫色灯火同处一灯盏之中！\n"NOR,me,target);   
		                        message_vision(HIM"\n$N"+HIM+"只得停下剑舞，面上尽是哀伤神色，$n"+HIM+"不觉一愣，$N"+HIM+"借机挥剑强攻！\n"NOR,me,target);
					COMBAT_D->do_attack(me, target, weapon);
				}
			}
	                else
	                {
	                        message_vision(HIC"\n忽然那梵音清唱，竟然罩定了青色火苗，青色火苗努力挣扎却是无力回天！\n"NOR,me,target);      
	                       	message_vision(HIM"\n$N"+HIM+"突然停下，象是在低头思索经文的意义，$n"+HIM+"不觉一愣，$N"+HIM+"借机挥剑猛攻！\n"NOR,me,target);
	                        COMBAT_D->do_attack(me, target, weapon);
	                }
        	}
	        else
	        {
	               	message_vision(HIC"\n$n"+HIC+"定睛一看，原来那神灯，在一张巨大的佛掌之上！\n"NOR,me,target); 
	                message_vision(HIM"\n$N"+HIM+"停了剑舞,合掌一礼，$n"+HIM+"不觉一怔，$N"+HIM+"借机挥剑飞攻！\n"NOR,me,target);
	                COMBAT_D->do_attack(me, target, weapon);
	        }
   	}
	else
	{
		message_vision(HIC"\n$n"+HIC+"大喊：青霞、紫霞私离佛界，还念什么经文？！\n"NOR,me,target);
		message_vision(HIM"\n$N"+HIM+"鄙夷地看了$n"+HIM+"一眼，觉得这人很没有水准，$n"+HIM+"正纳闷，$N"+HIM+"已经挥剑攻了过去！\n"NOR,me,target);
	      	COMBAT_D->do_attack(me, target, weapon);
	}
        target->add_temp("apply/dodge",extra/5);
        target->add_temp("apply/parry",extra/5);
        me->add_temp("apply/attack",-extra/5);
    	me->add_temp("apply/damage",-extra/5);
        if ((target->query("kee") < 0 || !living(target)) && !random(5))
	{
		str=target->name()+HIM+"被"+me->name()+HIM+"用盘丝秘传"HIY"「日月同芯」"NOR+HIM"杀死了，据说"+target->name()+HIM+"的尸体竟然是半紫半青！";
                message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
	}
         me->set_temp("xin_end",time());
         return 1;
}
