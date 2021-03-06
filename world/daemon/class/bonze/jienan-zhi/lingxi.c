#include <ansi.h>

inherit SSERVER;
string* xuedao = ({
	"四白穴",
	"地仓穴",
	"大迎穴",
	"峡车穴",
	"头维穴",
	"下关穴",
	"隐白穴",
	"太白穴",
	"商丘穴",
	"地机穴",
	"少冲穴",
	"少海穴",
	"通理穴",
	"神门穴",
	"印堂穴",
	"金律穴",
	"玉液穴",
	"鱼腰穴",
	"百劳穴",
	"百会穴",
	"灵台穴",
	"太阳穴",
	"膻中穴",
	"命门穴",
	"鸠尾穴",
	"气海穴",
});

int perform(object me, object target)
{
        
	object *inv, obj, obj1;
   	int damage,jiali;
	int i, mypot,tapot;
	string str,xuename;
	int cd = 5;
        object weapon;
       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「灵犀指」？\n");

        if(!me->is_fighting(target))
                return notify_fail("「灵犀指」只能在战斗中使用！\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("你的内力不够！\n");
      	if(me->query("family/family_name") != "南海普陀山" )
                return notify_fail("你是哪儿偷学来的武功！\n");

        if((int)me->query("force") < 600 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

	i=(int)me->query_skill("jienan-zhi",1);

        if( i < 120)
                return notify_fail("你的劫难指级别还不够，使用这一招会有困难！\n");
	jiali = me->query("force_factor")+1;
	damage = me->query_skill("jienan-zhi", 1) + jiali;
	//if(damage > 500) damage = 500;
	
	if( me->query("lunhui_zhuanshi") )
		cd = 4;
        if( time()-(int)me->query_temp("lingxi_end") < cd )
                return notify_fail("你现在内息不顺！\n");
	message_vision(HIY"\n$N心悟佛法，灵犀所至，慧眼顿开，$N窥破$n招式的破绽，伸出右手食指凌空点下。\n"NOR,me,target);
	mypot = (int)me->query("combat_exp")/10000;
	tapot = (int)target->query("combat_exp")/12000;
       	
        if( random( mypot ) > tapot/3 || !living(target) ) 
	{       
             	xuename = xuedao[random(sizeof(xuedao))];
             	message_vision(HIY"\n只听见「嗤」的一声轻响$N的食指正打在$n的"+xuename+"上，$n登时浑身酸麻动弹不得。\n"NOR,me,target);
              	target->start_busy(2+random(2));
		message_vision(HIY"\n$N见$n果然中招，大喝一声，再点出一道指力！\n"NOR,me, target);	
		message_vision(HIR"\n指力透过"+xuename+"在$n经脉内四处冲突，$n痛苦不堪！\n"NOR,me, target);
		target->receive_damage("kee", damage, me);
		target->receive_damage("sen", damage, me);
	        target->receive_wound("kee",damage,me);
         	target->receive_wound("sen",damage,me);
	 	COMBAT_D->report_status(target);
		COMBAT_D->report_sen_status(target);
	 	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
         	{
         		str=target->name()+HIM"被"+me->name()+"的"+NOR+HIY"灵犀指力"+NOR+HIM"打中"+xuename+"，登时七孔流血而死。";
    			message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
		}
	}	 
	else if( random(mypot+tapot) > tapot/2 )
	{
		message_vision(HIY"$N识得厉害，拼命运转心法，停下招式，立在原地不敢动弹！\n"NOR, target);
		target->start_busy(2+random(3));
	        me->start_busy(1);
	}
	else
	{
		message_vision(HIC"$N识得厉害，连忙使一个鹞子翻身躲开了！\n"NOR, target);
	        me->start_busy(2);
	}       
        me->add("force", -i/5);
	me->receive_damage("sen", i/5);
	me->set_temp("lingxi_end",time());
        return 1;
}




