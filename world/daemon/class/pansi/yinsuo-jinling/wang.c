// chan.c �������塸���޵�����

#include <ansi.h>
inherit SSERVER;
int checking(object me, object target, object weapon);

string *number_msg = ({"һ","��","��","��","��","��","��","��","��","ʮ","ʮ��","ǧ��","����"});
string *whip_msg = ({"����","б��","���","�ᶶ","����","ֱ��","����","ǰ��"});

string *chan_msg = ({
HIC"$N"HIC"�������ޣ�$S���$R��"HIR"ԲȦ"HIC"����ǧ���򻯣������޾���Ҫȥ������ס$n"HIC"��\n\n" NOR,
HIC"$N"HIC"�������ޣ�$S���$R��"HIR"ԲȦ"HIC"��ǰ�����У�Ҫ��$n"HIC"����������\n\n" NOR,
HIC"$N"HIC"���в��������ң��������ޣ�$W"HIC"ÿ��һ�У����Ʒų�һ��"HIR"ϸ˿"HIC"��Ҫȥ��ס$n"HIC"��\n\n"NOR,
HIC"$N"HIC"�������ޣ�$S���$R��"HIR"ԲȦ"HIC"�������ཻ��Ҫ��$n�������У�\n\n" NOR,
HIC"$N"HIC"����$W"HIC"�Ӷ�������������ɢ��������"HIR"ϸ˿"HIC"��Ҫ��$n"HIC"��������\n\n"NOR,
HIC"$N"HIC"�������ޣ�$S���$R��"HIR"ԲȦ"HIC"�����°��ݣ�Ҫ��$n"HIC"����������\n\n" NOR,
HIC"$N"HIC"��һ��$W"HIC"����һ����"HIR"ԲȦ"HIC"��ÿһ�о����Ի��δ̳����Ի����ջأ���ס$n"HIC"��\n\n"NOR,
HIC"$N"HIC"�������ޣ�$S���$R��"HIR"ԲȦ"HIC"�����Ҽ�ˣ�Ҫ��$n"HIC"�������У�\n\n" NOR,
});

string *dodged = ({
HIY"����$n"HIY"��Ȼ������$P"HIY"����������עһ��ֱ��Ȧ�ģ�����$N"HIY"��������⣡\n\n" NOR,
HIY"$n"HIY"΢��$N"HIY"����ɬ�ͣ���æ���У��߾�ȫ��֮���й�����������˿Ȧ�г��˳�ȥ��\n\n"NOR,
HIY"$n"HIY"΢��$N"HIY"����ɬ�ͣ���æ���У��߾�ȫ��֮����Ծ���ˣ�Զ���˱�����\n\n"NOR,
HIY"$n"HIY"�������У��������й�����������һԾ�����ӳ�Ȧ�⡣\n\n"NOR,
});

string *chaned = ({
HIW"���$n"HIW"����������ɬ�ͣ�ż������һ�У������˵ò��㣬�㱻$W"HIW"������ת����Ȧ�ӡ�\n"NOR,
HIW"�����������ɢ������ϸ˿Խ��Խ�࣬���ǻ�����һ����˿�ޣ���$n"HIW"��������������\n"NOR,
HIW"����������������ǻ�����һ����˿�ޣ���$n"HIW"��������������\n"NOR,
HIW"$n"HIW"Խ��Խ�Ǻ��£�һ������������������������������\n"NOR,
});

int perform(object me, object target)
{
//		string msg;
        object weapon = me->query_temp("weapon");
        int cost = me->query_skill("yinsuo-jinling", 1)/2;
        string msg;
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(!living(target))
                return notify_fail("���˱����Ͳ��ܶ�,������ʲô���޵�����\n");
        if(!weapon || (weapon->query("skill_type") != "whip" && !me->is_manmade_npc()) )
                return notify_fail("�������ޱޣ����ʹ�á����޵�������\n");
		if(me->query("family/family_name")!="��˿��")
return notify_fail("�����޵�����ֻ����˿�����˲ſ����ã�\n");
        if(me->query_temp("YSJL/chan"))
                return notify_fail("������ʹ�á����޵�������\n");
        if( target->is_busy() )
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
        if( (int)me->query_skill("yinsuo-jinling", 1) < 100 )
                return notify_fail("����������弫������죬��Ҫ���������ˡ�\n");
        if( me->query("force") < 500 )
                return notify_fail("�������������\n");
        if( me->query("mana") < 500 )
                return notify_fail("��ķ���������\n");
        if(me->query_temp("combat_wield"))
                return notify_fail("�㲻���ޣ�����֯�������޵�������\n");
        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                 return notify_fail("�������޷�ʹ�á����޵�������\n");
        if(userp(me)){
    
            if( (int)me->query_skill("pansi-dafa", 1) < 100 )
                return notify_fail("�����˿����Ϊ���������ܰ����б������������޵�������\n");
            if( me->query_skill_mapped("force") != "jiuyin-xinjing")
                return notify_fail("�����õ��ڹ�����������������㣣�\n");
            }
        me->add("force", -100);
        me->add("mana", -100);

        message_vision(HIW"\n$NĬ����˿��,��������һ������˿��"+weapon->name()+HIW"����Ʈ��,�ڿ�����һȦȦ���ţ�
���಻��������������һ�Ŵ���������$n"HIW"�ս���\n\n"NOR, me, target);
	  msg = chan_msg[random(sizeof(chan_msg))];
 	  msg = replace_string(msg, "$S", whip_msg[random(sizeof(whip_msg))]);
          msg = replace_string(msg, "$R", number_msg[random(sizeof(number_msg))]);
          msg = replace_string(msg, "$W", weapon->name());
          message_vision(msg,me, target);
	//if( ((random(me->query("combat_exp")) + (me->query("combat_exp")/2) > (int)target->query("combat_exp")*1/2 ))) {
	if( random(me->query("combat_exp")) > target->query("combat_exp")/5 ) {
		msg = chaned[random(sizeof(chaned))];
          	msg = replace_string(msg, "$W", weapon->name());
          	message_vision(msg,me, target);
		target->start_busy(3);
//		me->start_busy(random(2));
	} else {
		msg = dodged[random(sizeof(dodged))];
          	msg = replace_string(msg, "$W", weapon->name());
          	message_vision(msg,me, target);
                me->start_busy(random(2));
	}
//	message_vision(msg, me, target);
//        target->start_busy(3);
//        me->start_busy(1);
        //me->set_temp("YSJL/chan", 1);
        //call_out("check_fight", 2, me, target, weapon);
    	//me->start_perform(1, "��");
        return 1;
}

int check_fight(object me, object target, object weapon)
{
        string msg;
        object wep;

        if (!me) return 1;
        if(!me->query_temp("YSJL/chan")) return 1;

        if(!living(me) || !target){
           me->delete_temp("YSJL/chan");
           return 1;
        }
        
        if(!objectp(wep = me->query_temp("weapon")) || (wep->query("skill_type") != "whip" && !me->is_manmade_npc())){
           if(!wep)msg = HIY"$N����������ʧ��Բת��������˿Ҳ��֮��ɢ��$n�������˿�����\n"NOR;
           else  msg = HIY"$N����"+wep->name()+HIY"���������б�����$n����ܲ���˿��Ҳ��֮��ɢ��ѹ����Ȼ���ᣡ\n"NOR;
           if(target->is_busy()) target->start_busy(1);
           me->start_busy(1);
           me->delete_temp("YSJL/chan");
           message_vision(msg, me, target);
           return 1;
           } 
        if(environment(me) != environment(target)){
        	msg = HIY"$N������"+wep->name()+HIY"���һ�ڣ���Բ��һ��������ɢ����"+HIW"�����޵�����"+HIW"��\n"NOR;
                me->delete_temp("YSJL/chan");
                message_vision(msg, me, target);
                return 1;
                }
        if(!me->is_fighting(target) && !me->is_killing(target->query("id"))){
           if(!living(target)) msg = HIY"$N��м������$nһ�ۣ�������"+wep->name()+HIY"һ���ڣ�������ɢ����"+HIW"�����޵�����"+HIW"��\n"NOR;
           else msg = HIY"$N������"+wep->name()+HIY"���һ�ڣ���Բ��һ��������ɢ����"+HIW"�����޵�����"+HIW"��\n"NOR;
           if(target->is_busy()) target->start_busy(1);
           me->delete_temp("YSJL/chan");
           message_vision(msg, me, target);
           return 1;
           }           

        if(wep != weapon){
           message_vision(HIY"$N�����˱��������ƶ�ʱ�޷�Բת���⣬$n��ߵ�"+HIW"�����޵�����"+HIY"���������ʹ$n���˴�Ϣ֮���ᣡ\n"NOR,me, target);
           me->start_busy(1);
           if(target->is_busy() 
              && random(me->query_skill("yinsuo-jinling", 1)) < (int)target->query_skill("dodge", 1)/2){
              target->start_busy(1);
              me->delete_temp("YSJL/chan");
              return 1;
              }
           else {
		call_out("checking", 1, me, target, wep);
		me->start_perform(1, "��");
	   }
          }
       if (userp(me) && (me->query_skill_mapped("whip") != "yinsuo-jinling" || (me->query_skill_mapped("parry") != "yinsuo-jinling") && !me->is_manmade_npc())){
           message_vision(HIY"$NͻȻ���У�����"+HIW"�����޵�����"+HIY"��ʹ��������������ȫ��ͬ����������\n"NOR,me);
           if(target->is_busy()) target->start_busy(3);
           me->start_busy(1);
           me->delete_temp("YSJL/chan");
           return 1;
           }   
       if( me->query("force") <= me->query_skill("yinsuo-jinling", 1)/2 ){
           message_vision(HIY"$N��ʽ����ɬ�ͣ�ż��һ�������Ȼ����������ԭ�������������ˣ�\n"NOR,me);
           if(target->is_busy()) target->start_busy(1);
           me->start_busy(1);
           me->delete_temp("YSJL/chan");
           return 1;
           }           
       if(!target->is_busy() && !me->is_busy() && random(4)==1 && living(target)){
          msg = chan_msg[random(sizeof(chan_msg))];
          msg = replace_string(msg, "$S", whip_msg[random(sizeof(whip_msg))]);
          msg = replace_string(msg, "$R", number_msg[random(sizeof(number_msg))]);
          msg = replace_string(msg, "$W", wep->name());
          message_vision(msg, me, target);
          checking(me, target, wep);
          }
       else {
	call_out("check_fight", 1, me, target, wep);
	me->start_perform(1, "��");
       }
       return 1;
}       


int checking(object me, object target, object weapon)
{
        string msg;
        int busy_time, ap, dp, cost;
        cost = 20 * target->query_temp("YSJL/chan"+me->query("id")) + me->query_skill("yinsuo-jinling", 1)/2;
        busy_time = (int)me->query_skill("yinsuo-jinling", 1)/20;
        ap = me->query("combat_exp")/1000 * me->query_skill("yinsuo-jinling",1) * me->query_int();
        dp = target->query("combat_exp")/1000 * target->query_skill("dodge",1) * target->query_int();
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("force", -cost);
        me->add("mana", -100);
        if(random(ap) > dp/2){          
          target->start_busy(3+random(busy_time));
          msg = chaned[random(sizeof(chaned))];
          msg = replace_string(msg, "$W", weapon->name());
          message_vision(msg, me, target);
          call_out("check_fight", 1, me, target, weapon);
	  me->start_perform(1, "��");
          }
        else{
          me->start_busy(3);
          me->delete_temp("YSJL/chan");
          msg = dodged[random(sizeof(dodged))];
          msg = replace_string(msg, "$W", weapon->name());
          message_vision(msg, me, target);
          }
       return 1;
}       


