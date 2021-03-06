/*天地万物皆有灵性，分五行。
所谓五行者，金木水火土，乃宇宙之根本，分化繁衍，遂成大千世界。
而天地大法，便在于五行之道。五行之道，有相生相克之说。
相克即金克木、木克土、土克水、水克火、火克金。相生即金生水、水生木、木生火、火生土、土生金。
人言五属魔法必定据此相生相克。此大谬也。
君不见烈火涸水，洪水决堤乎？此则火亦可克水，水亦可克土。
拘泥五行相克之论，刻舟求剑耳。五行根本之道，非相克，非相生，而在于相化也。
以薪火之力，可以沸锅水。然以薪火之力安能沸江湖邪？非火不可克水，势不足矣。
水火相克在于彼此之势，势不敌则力不逮。力不逮时安奈何？
惟有变化矣。以强势之火，敌若势之水，则火克水。
以等势之水火相敌，火恐不逮。倘能化火为等势之土，则可以克水。
以若势之火，敌强势之水，火必被克。但倘能化火为等势之水，则可以求生。
万物均有五属灵性，因强弱而分五行。木属之物，并非全无金水火土四性，相较弱耳。
而其五行属性无时不在变化之中，此则何以沧海为桑田也。
五行相化，便是以意念力控制某物或自身之五行属性，调整变化，顺应时势也。
言易行难，若无极强之念力、五行修行之体验，自然无法作到。上古至今，能五行变化者，不过九人而已。
欲五行相化，必先修五行之意。五行之金木水火土，其根本为‘恒’、‘生’、‘变’、‘亡’、‘容’也。
即永恒、生长、变化、毁灭、包容五道耳。五行为万物之基，亦为万物之律。
*/
// wuxing.c  五行相生相克合一为太极，由太极而入无极（黑洞）
//西金：moon,kunlun,shushan
//东木：pansi,sanxian,fc
//北水：xueshan,longgong
//南火：putuo,hyd,hell
//中土：jjf,wdd,wzg
//金水木火土 相生
//金木土水火 相克
#include <ansi.h>
inherit SSERVER;
mapping menpai = ([
		"陷空山无底洞"	:"土",
		"将军府"	:"土",
		"五庄观"	:"土",
		"火云洞"	:"火",
		"南海普陀山"	:"火",
		"阎罗地府"	:"火",
		"大雪山"	:"水",
		"东海龙宫"	:"水",
		"方寸山三星洞"	:"木",
		"盘丝洞"	:"木",
		"三界散仙"	:"木",
		"月宫"		:"金",
		"昆仑山玉虚洞"	:"金",
		"蜀山派"	:"金"
	]);
mapping xiangke = ([
		"金":"火",
		"木":"金",
		"土":"木",
		"水":"土",
		"火":"水"
	]);
mapping xiangsh = ([
		"金":"水",
		"木":"火",
		"土":"金",
		"水":"木",
		"火":"土"
	]);
mapping color = ([
		"金":HIW"金"NOR,
		"木":HIC"木"NOR,
		"土":HIY"土"NOR,
		"水":BLK"水"NOR,
		"火":HIR"火"NOR
	]);
string *wuxing = ({"金","木","土","水","火"});
int perform(object me, object target)
{
        string msg,f_name,str;
        int damage, ap, dp, i;
        int cd = 10;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你没有对手啊？！\n");
         if(!wizardp(me) && me->query("family/family_name") != "五庄观")
                return notify_fail("[五行]是五庄观不传之密！\n");
        if( !me->is_fighting(target) )
                return notify_fail("大家都很忙，没人有时间看你表演。\n");
        if (!me->query("wuxing_known"))
                return notify_fail("你还没有领悟到五行的内涵。\n");
        if (me->query_skill("wuxing-quan",1)<200)
                return notify_fail("你的五行拳不够，无法体会五行的内涵。\n");
        if (me->query_skill("unarmed",1)<200)
                return notify_fail("你基本拳脚不够，无法发挥五行的威力。\n");
        if (me->query_skill("literate",1)<200)
                return notify_fail("你的读书识字不够，无法体会五行的内涵。\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力还不到火候。\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
	if( time() - (int)me->query_temp("wuxing_time") < cd )
                 return notify_fail("绝招用多，就不灵了。\n");
        me->set_temp("wuxing_time",time());            
        ap = me->query_skill("wuxing-quan",1);    
        dp = me->query_skill("dodge",1);
        damage = me->query_skill("unarmed") + me->query("force_factor");
        damage = damage*2 + random(damage);
        damage = damage - target->query_temp("apply/armor");
        if( damage < (me->query_skill("unarmed",1) + me->query("force_factor")) ) 
        	damage = me->query_skill("unarmed") + me->query("force_factor");
 	f_name = target->query("family/family_name");
 	me->add("force",-damage/3);
 	if( me->query("wuxing_known") == 1 )
 	{
 		if( !f_name )
 		{
			damage = damage * 6 / 5 + random(damage/5);
 			str = wuxing[random(sizeof(wuxing))];
 			msg = HIM"\n$N运转体内五行之力打出一拳，一股"+BLINK+ color[str] +HIM"性内力扑向$n！\n"NOR;
 		}
 		else
 		{
        		damage = damage * 5 / 4 + random(damage/4);
        		str = xiangke[menpai[f_name]];
        		if( !stringp(str) || str == "" || str == "0" )
        			str = wuxing[random(sizeof(wuxing))];
        		msg = HIM"\n$N明辨$n五行属性，运转体内"+BLINK+color[str]+HIM"之力，全力打出一拳！\n" NOR;
        	}
       	}
       	else if( me->query("wuxing_known") == 2 )
       	{
       		if( !f_name )
 		{
 			damage = damage * 4 / 3 + random(damage/3);
 			str = wuxing[random(sizeof(wuxing))];
 			msg = HIM"\n$N调动体内五行之力，将"+BLINK+color[str]+HIM"之力融入";
 			str = xiangsh[str];
 			msg =  msg +BLINK+ color[str] + HIM"之力，真气相生相激，犹如春江滚滚，土崩冰裂！\n"NOR;
 			msg =  msg + HIB"$N一声清啸，鼓动全身真气，朝$n当胸打出一拳！\n"NOR;
 		}
 		else
 		{
        		me->add("force",damage/5);
        		damage = damage * 3 / 2 + random(damage/2);
        		str = menpai[f_name];
        		if( !stringp(str) || str == "" || str == "0" )
        			str = wuxing[random(sizeof(wuxing))];
        		msg = HIM"\n$N运转五行心法，将$n使用的"+BLINK+color[str]+HIM"之力吸纳入体，再以心法引导流过\n"NOR;
        		for(i=0;i<3;i++)
        		{
        			str = xiangsh[str];
        			if(i==0) msg =  msg +"\n\t"+BLINK+ color[str] + HIM"之力\n"NOR;
        			if(i==1) msg =  msg +"\n\t\t"+BLINK+ color[str] + HIM"之力\n"NOR;
        			if(i==2) msg =  msg +"\n\t\t\t"+BLINK+ color[str] + HIM"之力\n"NOR;
        		}
        		msg =  msg + HIM"五行真气相生相激，犹如春江滚滚，土崩冰裂！\n"NOR;
        		msg =  msg + HIB"$N一声清啸，鼓动全身真气，朝$n当胸打出一拳！\n"NOR;
        	}
       	}
       	else
       	{
        	me->add("force",damage/4);
        	damage = damage * 2 + random(damage);
        	msg = HIW"\n$N运转五行心法，以本身"+BLINK+HIY"土"+NOR+HIW"之力带行"+BLINK+HIW"金"+BLK"水"+HIC"木"+HIR"火"+NOR+HIW"其他四行。\n"NOR;
        	msg =  msg + HIC"\n五行真气相生相激，进而阴阳分化，化作两道洪流分行奇经八脉。\n"NOR;
        	msg =  msg + HIC"\n阴阳真气慢慢汇聚于任、督二脉，由动入静。\n"NOR;
        	msg =  msg + HIY"\n下一瞬间，原本就要静止的两道真气，同时冲向$N的生死玄关。\n"NOR;
        	msg =  msg + HIM"\n$N和$n彷佛听到一声极大的轰鸣，起于心底，散之天地！\n"NOR;
        	msg =  msg + HIM"\n$N体内真气化作一道长虹，贯穿天地桥梁，天地间的浩然正气，滚滚而来！\n"NOR;
        	msg =  msg + HIM"\n$N将无坚不摧的浩然正气，聚于拳头之上，挥出一拳！\n"NOR;
        	msg =  msg + RED"\n$n被$N气劲压的喘不过起来，脸上现出恐怖的神情！\n"NOR;
       	}
       	message_vision(msg, me, target);
       	if( me->query("wuxing_known") <= 2 )
       	{
       		switch (str)
        	{
                       	case "金":
                       	{ 
                       		msg = target->name()+HIM"被"+me->name()+HIM"使用五庄观绝学「"+HIW+"太极"+HIB+"五行"+HIM"」中的"+BLINK+HIW"金"+NOR+HIM"之力杀死了，尸体上伤口无数，惨不忍睹！";
                       		message_vision(WHT"\n$n只觉一股大力迎面而来，有如利刃临体！\n"NOR,me,target);
                               	break;
                       	}
	                case "水": 
	                {
	                       	msg = target->name()+HIM"被"+me->name()+HIM"使用五庄观绝学「"+HIW+"太极"+HIB+"五行"+HIM"」中的"+BLINK+BLK"水"+NOR+HIM"之力杀死了，尸体骨骼尽碎，不成形状！";
	                       	message_vision(CYN"\n$n只觉一股大力将自己团团围住，有如置身大海，无法立足！\n"NOR,me,target);
	                        break;
	                }
	                case "木":
                       	{ 
                       		msg = target->name()+HIM"被"+me->name()+HIM"使用五庄观绝学「"+HIW+"太极"+HIB+"五行"+HIM"」中的"+BLINK+HIC"木"+NOR+HIM"之力杀死了，尸体被野花覆盖，变成了花肥！";
                       		message_vision(HIG"\n$n只觉一股大力由四面八方而来，四周植物疯狂生长蔓延！\n"NOR,me,target);
                               	break;
                       	}
                       	case "火":
                       	{ 
                       		msg = target->name()+HIM"被"+me->name()+HIM"使用五庄观绝学「"+HIW+"太极"+HIB+"五行"+HIM"」中的"+BLINK+HIR"火"+NOR+HIM"之力杀死了，尸体被烧得焦黑，再辨不出生前模样！";
                       		message_vision(RED"\n$n只觉一股火热扑面而来，如烈日当空，浩漠千里，四周再无一丝生机！\n"NOR,me,target);
                               	break;
                       	}
                       	case "土":
                       	{ 
                       		msg = target->name()+HIM"被"+me->name()+HIM"使用五庄观绝学「"+HIW+"太极"+HIB+"五行"+HIM"」中的"+BLINK+HIY"土"+NOR+HIM"之力杀死了，尸体早已被黄土覆盖，再无痕迹！";
                       		message_vision(YEL"\n$n只觉一股大力从脚下大地传来，一时间地动山摇，再也无法立足！\n"NOR,me,target);
                               	break;
                       	} 
		}
       	}
       	else
       		msg = target->name()+HIM"被"+me->name()+HIM"使用五庄观绝学「"+HIW+"太极"+HIB+"五行"+HIM"」杀死了，从尸体上看不出任何痕迹！";
       	if( random(ap+dp) > dp/(1+me->query("wuxing_known")) )
       	{
       		message_vision(HIR"\n$n着实无法抵挡，被$N劲力实实击中，“哇”的吐出一口鲜血，看来受了极重的内伤！\n"NOR,me,target);
       		target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
		if(wizardp(me)) tell_object(me,HIY"damage:"+ damage +"\n");
		COMBAT_D->report_status(target);
       	}
       	else
       	{
       		message_vision(HIB"\n$n极力要稳住身形，不想脚下一个踉跄，却刚好躲过了$N的劲力！\n"NOR,me,target);
       	}
       	//暂时不开放，增加个谣言玩玩
       	/*if( me->query("wuxing_known") > 2 && !userp(target) )
       	{
       		message_vision(HIW"\n$N脚下突然现出一个太极图案，$N脚踏阴阳，慢慢升入空中！\n"NOR,me,target);
       		message_vision(HIW"\n$N将吸纳而来的浩然正气转化为阴阳二气，经由双脚输入脚下太极之中！\n"NOR,me,target);
       		message_vision(HIW"\n太极图吸纳了真气后，陡地一震将$N弹开，飞到$n的上空，并开始旋转！\n"NOR,me,target);
       		message_vision(HIW"\n太极图越转越快，到得最后只剩下了一个漆黑的小点。$N若有所悟，对太极五行的领悟又深了一层！\n"NOR,me,target);
       		message_vision(HIW"\n$n却是另外一番感受，太极图中传来无穷无尽的吸引力，彷佛要将$n带入另外一个世界！\n"NOR,me,target);
       		message_vision(HIW"\n$n渐渐离地而起，被吸入半空，$N只听见“嗖”的一声，$n已经被吸入了太极图中，而太极图同时消失不见了！\n"NOR,me,target);
       		str=me->name()+HIM"使出五庄观绝学「"+HIW+"太极"+HIB+"五行"+HIM"」，"+target->name()+HIM"被太极图带入了异世界，看来这辈子是回不来了！";
		message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
       	}
       	else*/
       	//{
       		if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
        	{
			message("channel:rumor",HIM"【空穴来风】某人："+msg+"\n"NOR,users());
		}	
       	//}
        return 1;
}
