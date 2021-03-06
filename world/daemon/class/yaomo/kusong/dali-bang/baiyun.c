//perform baiyun 四连招
//created by vikee
//2000.10
//modify by huarong 2003.11
#include <ansi.h>

inherit SSERVER;

string *baiyun= ({
BLINK""HIR"\n千江有水千江月，万里无云万里天。"NOR,
BLINK""HIG"\n黄菊篱边无怅望，白云乡里有温柔。"NOR,
BLINK""CYN"\n抬眼一望天如洗，笑思白云聚山巅。"NOR,
BLINK""MAG"\n远上寒山石径斜, 白云深处有人家。"NOR,
BLINK""HIY"\n白云在天不可呼，白云在地不可孤。"NOR,
BLINK""HIB"\n仰首遥视上天林，峰吐白云醉人景。"NOR,
BLINK""HIM"\n黄河远上白云间，一片孤城万仞山。"NOR,
BLINK""HIC"\n月中未要恨丹桂，岭上且来看白云。"NOR,
BLINK""HIW"\n白云生远岫，摇曳入晴空。"NOR,
BLINK""RED"\n但去莫复问，白云无尽时。"NOR,
});


int perform(object me, object target)
{
         
        string str;       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「白云无尽」？\n");

        if(!me->is_fighting())
                return notify_fail("「白云无尽」只能在战斗中使用！\n");

        if((int)me->query("max_force") < 500 )
                return notify_fail("你的内力不够！\n");

        if (me->query_skill_mapped("force")!="huomoforce")
                return notify_fail("「白云无尽」必须配合火魔心法才能使用。\n");
                
        if((int)me->query_skill("huomoforce",1) <50)
                return notify_fail("你的火魔心法级别还不够，使不出「白云无尽」！\n");

     if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("dali-bang", 1) < 50)
                return notify_fail("你的大力棒法级别还不够，使用这一招会有困难！\n");

        if( time()-(int)me->query_temp("baiyun_end") < 6 )
                return notify_fail("绝招用多了就不灵了！\n");

        me->delete("env/brief_message");
        target->delete("env/brief_message");

	message_vision(HIY"\n$N大吼一声，犹如晴天霹雳，猛的祭出了大力棒的杀手绝学「白云无尽」!\n"NOR,me,target);
	me->set_temp("DLB_perform", 1);
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        message_vision(baiyun[random(sizeof(baiyun))], me, target);
        message_vision(HIB+"\n>>>>>>>>>>>"+NOR, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->delete_temp("DLB_perform");
	if ( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && random(5)==1 )
        {
        	str=target->name()+HIM"被"+me->name()+HIM"用火云秘传"NOR+HIY+"「白云无尽」"
	            +HIM"打碎全身骨节，再也看不出他生前是什么模样！";
        	message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
        }

        me->receive_damage("sen", 100);
        me->add("force", -100-(int)me->query_skill("dali-bang",1)/5);

        me->set_temp("baiyun_end",time());
        //me->start_busy(1+random(2));
        return 1;
}




