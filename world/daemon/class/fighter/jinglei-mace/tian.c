// tian.c by single
//this perform have too large damage, aqing medifyed it
//and solved the nk problem
// aqing 2000.9.30
// 修改by canoe ,05-13-2001
// 对齐了描述,攻击力确实可怕,改小了
// 这个pfm很cool
#include <ansi.h>
inherit SSERVER;

string begin_msg(object me,object target,int i,string w_name);
int perform(object me,object target)
{

string *l_weapon = ({
	"dodge",
	"unarmed",
	"spear",
        "archery",
	"axe",
	"mace",
	"mace",
});
string *fail_msg = ({
	"但是$n却乱闯一通，误打误撞，竟然将$N辛苦布成的阵法破坏了。\n",
	"就在$N的拳头要击中$n的瞬间，$n猛然大叫了一声，$N一受惊，一下收了回来。\n",
	"$n竟然看出身旁的火焰是幻影，丝毫不受$N幻影攻击的影响。\n",
	"哪知$n早已料到这招，凭着一口真气，一越而上，愣是从万箭之中逃了出去。\n",
	"$n急忙飞身向后跃出数丈，才勉强躲闪过这致命一击。\n",
	"$n以柔克刚，以阴克阳，愣是让$N的雷霆一击之力化为乌有。\n",
	"想不到$n逆转心法，硬是抗下了$N海纳百川的绝学。\n",
});
string *succ_msg = ({
       "$n只觉得四周有无形之力向自己压来，身形顿时慢了下来。\n",
       "$n向后急退，最后退无可退，硬生生的接了$N一拳，只觉得五脏六腑都移了位。\n",
       "$n手足无措，被烈火灼伤了胸部，$n心理精神上受到了很大的打击。\n",
       "$n一时慌了神，只听”嗤嗤”几声，原来已经被利箭射的身上千疮万孔。\n",
       "结果一道寒光从$n当头劈过,带出一地鲜血。\n",
       "$n来不及细想，凭感觉躲闪，但来不及了，肩膀愣是被砸中，顿时行动受损。\n",
       "$n抵挡不住，拼命咬破舌尖，激发潜力平息了精气的骚动。\n",
});
	object weapon,temp;
	int ap,dp,flag,i,damage,damage_flag;
	string *w_temp,w_name;
	string msg;

    	string str; 
	string unarmed,dodge,axe,mace,spear,archery;
	int cd = 8;
	if(!target)      target = offensive_target(me);
	if(!wizardp(me)&&(string)me->query("family/family_name") != "将军府" )
		return notify_fail("你不是将军府门下，如何能领悟得了此招「浑然天成」？\n");
	
	if( me->query("lunhui_zhuanshi") > 1 )
		cd = 6;
	else if( me->query("lunhui_zhuanshi") )
		cd = 7;
	if( time()-(int)me->query_temp("xiao_end") < cd )
		return notify_fail("绝招用多就不灵了！\n");
	if(!target
	|| !target->is_character()
	|| target->is_corpse()
	|| target == me )
		return notify_fail("你准备对谁用这招「浑然天成」？\n");
	
	if(!me->is_fighting(target))
		return notify_fail("「浑然天成」必须在战斗中才能使用．\n");
	if( me->query("sen") < 500 )
		return notify_fail("你的精神不足，使用这招「浑然天成」恐怕有危险．\n");
	if( me->query("kee") < 500 )
	 return notify_fail("你的气血不足，使用这招「浑然天成」恐怕有危险。\n");
		 
	if( me->query("max_force") < 1200 )
		return notify_fail("你的内力根本不足以使用这招「浑然天成」．\n");
	if( me->query("force") < 800 )
		return notify_fail("你的当前内力太少了，会有危险的．\n");
	if( me->query("mana") < 800 )
		return notify_fail("你的当前法力太低，还无法熟练运用这招。\n");
	if( me->query_skill("lengquan-force",1) < 100 )
		return notify_fail("你的冷泉神功级别太低，还用不了这招．\n");
	if( me->query_skill("baguazhou",1) < 120 )
		return notify_fail("你的八卦咒级别太低，出不了此招．\n");
	if( me->query_skill("spear",1) < 100 )
		return notify_fail("你的基本枪法别太低，使用这招恐怕有危险．\n");
	if( me->query_skill("mace",1) < 100 )
		return notify_fail("你的基本锏法级别太低，还用不了这招．\n");
	if( me->query_skill("axe",1) < 100 )
		return notify_fail("你的基本斧法级别太低，还用不了这招．\n");
		
	weapon = me->query_temp("weapon");
	unarmed = me->query_skill_mapped("unarmed");
	spear = me->query_skill_mapped("spear");
	axe = me->query_skill_mapped("axe");
	mace = me->query_skill_mapped("mace");
	archery = me->query_skill_mapped("archery");
	dodge = me->query_skill_mapped("dodge");
	if( unarmed == "changquan" )  flag = 1;
	if( spear == "bawang-qiang" )  flag += 1;
	if( axe == "sanban-axe" )    flag += 1;
  if( mace == "jinglei-mace" )  flag += 1;
	if( archery == "xuanyuan-archery" )   flag += 1;

	if( flag < 3 )
		return notify_fail("你本门武功太少，无法使用这招「浑然天成」．\n");
	if( me->query_skill("wusi-mace",1) > 120 ) flag += 1;
	if( me->query_skill_mapped("force") != "lengquan-force" )
		return notify_fail("没有冷泉神功作基础，如何引发这招「浑然天成」？\n");
	if( me->query_skill_mapped("spells") != "baguazhou" )
		return notify_fail("没有八卦咒引导，如何将此招「浑然天成」发挥到最大限度？\n");
	msg = HIR"\n$N暗念八卦咒，运起澎湃护体真气，脚下是越转越快，出手是越来越狠．．．．\n"NOR;
	message_vision(msg,me);
//	me->start_busy(2+random(3));
	me->add("force",-400);
	me->add("mana",-300);
	if(userp(target))
		damage_flag = 0;
	else
		damage_flag = 1;
	for(i=0;i<sizeof(l_weapon);i++)
	{
	seteuid(getuid());
	if( !me->query_skill_mapped(l_weapon[i]) ||(int)me->query_skill(me->query_skill_mapped(l_weapon[i]),1) < 100 )
		continue;
	if(l_weapon[i]=="unarmed")
	{
		w_name = " ";
		msg = begin_msg(me,target,i,w_name);
	}
	else
	if(l_weapon[i]=="dodge")
	{
		w_name = " ";
		msg = begin_msg(me,target,i,w_name);
	}
	else
	{
		if(l_weapon[i]=="spear") temp=new("/d/obj/weapon/spear/biyuqiang"); 
        	if(l_weapon[i]=="axe") temp=new("/d/obj/weapon/axe/huafu"); 
           	if(l_weapon[i]=="mace") temp=new("/d/obj/weapon/mace/goldjian"); 
		if(l_weapon[i]=="archery") temp=new("/d/obj/weapon/archery/mugong"); 
        	temp->move(me);
		w_name = temp->query("name");
		msg = begin_msg(me,target,i,w_name);
	/*if ( i >= 6 || msg== "shake" )
         {      weapon->delete("equipped");
                temp->set("equipped","wielded");
                me->set_temp("weapon",temp);
                me->reset_action();
		message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,me->query_temp("weapon"));
                temp->delete("equipped");
                weapon->set("equipped","wielded");
                me->set_temp("weapon",weapon);
                destruct(temp);
                me->reset_action();
		continue;
	}*/
	}
        message_vision(msg,me,target);
	if(temp)
	destruct(temp);

	ap = me->query_skill(l_weapon[i], 1) + me->query_skill("force", 1) + me->query_skill("spells", 1);
	dp = target->query_skill("parry", 1) + target->query_skill("force", 1) + target->query_skill("dodge", 1);
    if (userp(me)) ap += me->query_skill("literate",1);
	if( !userp(target) )//对怪物的命中提高
		dp = dp*2/3;
	//if( random(ap) < random(dp*2/3) && userp(target) )
	//{	message_vision(fail_msg[i],me,target);
	//}
	//else
	if( random(ap + dp/2) < dp/2 )//&& !userp(target) )
	{       message_vision(fail_msg[i],me,target);
	}
	else
	{
		if( l_weapon[i] == "dodge" )
		{
			//me->add_temp("apply/dodge",(int)me->query_skill("dodge",1)/3);
		 	//me->add_temp("apply/attack",(int)me->query_skill("dodge",1)/3);
		 	//me->add_temp("apply/armor",(int)me->query_skill("dodge",1)/3);
		 	me->add_temp("apply/strength",(int)me->query_skill("dodge",1)/3);
			target->add_temp("apply/dodge",-(int)me->query_skill("dodge",1)/4);
			target->add_temp("apply/parry",-(int)me->query_skill("dodge",1)/4);
			me->set_temp("apply/dodge_add",1);
			message_vision(succ_msg[i],me,target);
			me->reset_action();
			continue;
		}		
		if( l_weapon[i] == "unarmed" )
		{
			message_vision(succ_msg[i],me,target);	
			damage = me->query_skill(l_weapon[i]) * (5+me->query("kai_known")) / 5 + random(me->query_skill(l_weapon[i]))/3;// + me->query("force_factor");
	                if(random(ap) > dp/2)
        	        {
                	        damage += me->query_str() + damage / 3;
                        	message_vision(CYN"\n轰!!轰!!轰!!$N被$n砸得天旋地转,站立不稳,差点去见崔叔叔!!\n"NOR,target,me->query_temp("weapon"));
	                }
        	        target->receive_damage("kee",damage/(1+damage_flag));
                	target->receive_wound("kee",damage/(2+damage_flag));
	                target->receive_damage("sen",damage/3);
	                target->receive_wound("sen",damage/6);
        	        target->set_temp("last_damage_from",me);
			COMBAT_D->report_status(target);
			COMBAT_D->report_sen_status(target, 0);
			continue;
		}
		weapon->delete("equipped");
	        if(l_weapon[i]=="spear") temp=new("/d/obj/weapon/spear/biyuqiang"); 
        	if(l_weapon[i]=="axe") temp=new("/d/obj/weapon/axe/huafu"); 
	        if(l_weapon[i]=="mace") temp=new("/d/obj/weapon/mace/goldjian"); 
        	if(l_weapon[i]=="archery") temp=new("/d/obj/weapon/archery/mugong"); 
	 	temp->move(me);
		temp->set("equipped","wielded");
	 	me->set_temp("weapon",temp);
		me->reset_action();
		message_vision(succ_msg[i],me,target,me->query_temp("weapon"));

		damage = me->query_skill(l_weapon[i]) * (5+me->query("kai_known")) / 5 + random(me->query_skill(l_weapon[i]))/3;// + me->query("force_factor");
		if(random(ap) > dp/2)
		{
			damage += me->query_str() + damage / 3;
			message_vision(CYN"\n轰!!轰!!轰!!$N被$n砸得天旋地转,站立不稳,差点去见崔叔叔!!\n"NOR,target,me->query_temp("weapon")); 
		}
             	target->receive_damage("kee",damage/(1+damage_flag));
                target->receive_wound("kee",damage/(2+damage_flag));
		target->receive_damage("sen",damage/3);
		target->receive_wound("sen",damage/6);
		target->set_temp("last_damage_from",me);
	        COMBAT_D->report_status(target);
		COMBAT_D->report_sen_status(target, 0);
        	temp->delete("equipped");
        	weapon->set("equipped","wielded");
        	me->set_temp("weapon",weapon);
        	destruct(temp);
        	me->reset_action();

	}
	}	
	if(me->query_temp("apply/dodge_add"))
	{
		//me->add_temp("apply/dodge", -(int)me->query_skill("dodge",1)/3);
		//me->add_temp("apply/attack",-(int)me->query_skill("dodge",1)/3);
		//me->add_temp("apply/armor",-(int)me->query_skill("dodge",1)/3);
		me->add_temp("apply/strength",-(int)me->query_skill("dodge",1)/3);
		target->add_temp("apply/dodge",(int)me->query_skill("dodge",1)/4);
		target->add_temp("apply/parry",(int)me->query_skill("dodge",1)/4);
		me->delete_temp("apply/dodge_add");
	}		 
       /*if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }*/
    if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
{str=target->name()+HIM"被"+me->name()+"用将军府秘传"NOR+HIR"「浑然天成」"+HIM"打死了，据说"+target->name()+"的尸体插满兵器！";
    message("channel:rumor",HIM"【空穴来风】某人："+str+"\n"NOR,users());
  }
    me->set_temp("xiao_end",time());
	return 1;
}
string begin_msg(object me,object target,int i,string w_name)
{
 	if(i==0)	
return (HIM"\n【布阵诀．．．．．．．．．．奇门八卦】"NOR+"\n$N口中念道：乾生天，坤生地，八卦无形，周转复始．绕着$n越转越快，\n同时在地上不知布了一些什么玄机.地上起了些奇异的变化！！！\n");
	if(i==1)
return (HIC"\n【勇气诀．．．．．．．．．．神勇无敌】"NOR+"\n$N叫道：“着”同时，双手交换出拳，一拳比一拳快，当真是\n有万夫莫敌之气势，将长拳发挥得淋漓尽致，直朝着$n而去。\n");
	if(i==2)
return (HIR"\n【枪字诀．．．．．．．．．．星火燎原】"NOR+"\n$N暗暗将咒语附着在"+w_name+"上，向四周虚劈了几下，所到之处，卷起层层烈焰，\n象是要把$n吞噬一样,$n的脸被火焰映得通红。\n");
	if(i==3)
return (HIY"\n【箭字诀．．．．．．．．．．百战百胜】"NOR+"\n$N将手中"+w_name+"往空中一抛，手指$n，叫道：去也。只见"+w_name+"不断射出利箭，\n利箭越来越多，从四面八方直朝着$n射去,$n顿时惊慌失措。\n");
	if(i==4)
return (HIB"\n【斧字诀．．．．．．．．．．力劈山河】"NOR+"\n $N突然暴喝一声，将手中"+w_name+"斜向上举起，\n然后在半空中划出一道圆弧，随即径直斜下斩向$n！\n");
	if(i==5)
return (HIW"\n【惊雷诀．．．．．．．．．．雷殛怒火】"NOR+"\n$N双手举起"+w_name+"，以雷霆万钧之势向$n砸去，此招看似大拙，实则大巧。\n"+w_name+"在空中一个转折,向$n飞来,$n脸上写满恐怖！\n");
	if(i==6)
return (HIG"\n【无私诀．．．．．．．．．．海纳百川】"NOR+"\n$N抛起"+w_name+"，合手念起八卦咒，$N彷佛化作大海，四周灵气向$N奔流而来。\n$n周身精气蠢蠢欲动，惊吓之下脸色变得苍白。\n");
else return ("shake");
}
