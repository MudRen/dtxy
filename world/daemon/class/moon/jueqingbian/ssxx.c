//kugu for moon
//2006 生死相许
/*
问世间、情是何物，直教生死相许。
天南地北双飞客，老翅几回寒暑。
欢乐趣，离别苦。就中更有痴儿女，君应有语，
渺万里层云，千山暮雪，只影为谁去。

横汾路，寂寞当年萧鼓。荒烟依旧平楚，招魂楚些何嗟及。
山鬼自啼风雨，天也妒。未信与、莺儿燕子俱黄土。
千秋万古。为留待骚人，狂歌痛饮，来访雁邱处。

*/ 
/*
          "恰如飞鸟倦知还，澹荡梨花深院。",
		"拂拂风前度暗香，月色侵花冷。",
		"不放玉花飞堕地，留在广寒宫阙。?,
		"把酒送春春不语，黄昏却下潇潇雨。?,
		"犹自风前飘柳絮，随春且看归何处。。",
		"愁病相仍，剔尽寒灯梦不成。",
		"伫立伤神，无奈轻寒著摸人。",
		"满院落花帘不卷，断肠芳草远。",
		"无绪倦寻芳，闲却秋千索。",
		"小院湘帘闲不卷，曲房朱户闷长扃",
*/
#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill,damage,ap,dp;
        string msg;
        int cd = 6;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展「生死相许」?\n");
        
	if( me->query("lunhui_zhuanshi") > 1 )
		cd = 5;
	if( time()-(int)me->query_temp("ssxx_end") < cd )
                return notify_fail("绝招用多就不灵了！\n");
        
        if(!me->is_fighting(target) )
                return notify_fail("生死相许只能在战斗中使用!!\n");

        if((int)me->query("max_force") <1000 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 1500 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") <1000 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("jueqingbian",1) <150)
                return notify_fail("你的绝情鞭级别还不够施展这一招生死相许!!\n");
        if((int)me->query_skill("moondance",1) <150)
                return notify_fail("你的冷月凝香舞等级不够!!\n");
        if((int)me->query_skill("moonforce",1)<150)
                return notify_fail("你的圆月心法等级太低!!\n");
        if((int)me->query_skill("moonshentong",1) <150)
                return notify_fail("你的月宫仙法等级不够!!\n");
        if( (string)me->query("gender") !="女性")
                return notify_fail("你非为纯阴之身,怎能知哓女儿家的心思??\n");
        if(me->query("family/family_name") != "月宫" )
                return notify_fail("你不是月宫弟子,领悟不到鞭法的精髓!!\n");
        me->set_temp("ssxx_end",time());
        skill = me->query_skill("whip",1);
        ap = me->query("combat_exp")/1000;
        dp = target->query("combat_exp")/1500;
        weapon=me->query_temp("weapon");
        msg = HIC"\n问世间情为何物？直教生死相许！$N心中一阵酸楚,再忍不住珠泪纵横！\n" NOR;
    	   message_vision(msg, me, target);
    	   msg = HIC"\n那眼泪水晶般晶莹剔透，落地亦是清脆有声！\n" NOR;
    	   message_vision(msg, me, target);
    	   if( random(ap) > dp/2 )
    	           msg = WHT"\n$n只觉那清脆的声音在心中不断响起，恍惚中两只燕儿冲天而起。\n" NOR;
    	   else
    	           msg = WHT"\n$n眼前一阵模糊，恍惚中两只燕儿冲天而起。\n" NOR;
    	   message_vision(msg, me, target);
    	   msg = HIC"\n两只燕儿傍依双飞，上青天，渺看万里层云、千山暮雪。\n" NOR;
    	   msg = msg + HIC"\n$n正在惊叹造化神奇，两只燕儿突然俯冲而下！\n"NOR;
    	   message_vision(msg, me, target);
    	   if( random( ap + dp ) > dp/2 )
    	   {
    	           damage = me->query_skill("whip") + me->query_skill("force") + me->query_str();
    	           damage = damage + random(damage/3);
	 	      damage = damage - target->query_temp("apply/armor");
	 	      if( damage < skill ) damage =  skill;
    	           msg = HIM"\n$n躲闪不及,被两只燕儿穿身而过！\n" NOR;
    	           target->receive_damage("kee",damage,me);
	           target->receive_wound("kee",damage/2,me);
	           message_vision(msg, me, target);
	           COMBAT_D->report_status(target);
	           me->add("force",-damage/6);
	           me->receive_damage("sen",damage/10);
    	   }
    	   else
    	   {
    	           me->add("force",-100);
	           me->receive_damage("sen",100);
    	           message_vision(HIB"\n$n镇定心神，眼前幻像消失了，心中微感遗憾。\n" NOR,me,target);
    	   }
        return 1;
}
