// mantian.c ��ϼ����
// ����ǳsword ��Ч�ȼ�180��ʱ�����������Լ����б��������齣Ϯ��
// �������sword ��Ч�ȼ�180��ʱ���Ϳ���ʩչ��蚣����齣��
// ���������н��������������call_out("perform_qiao", 10, me)
// �ý���ɱ�ˣ����������С������ļ�/d/pansi/obj/qiao
// daemon/class/pansi/qingxia-jian/mantian ��ϼ����
// jie 2001-2-4
 
#include <ansi.h>
 
inherit SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        object ob;
        int skill, skill2, ap, dp,damage,wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qingxia-jian",1);
        skill2 = me->query_skill("jiuyin-xinjing",1);
          if (userp(me) && !wizardp(me))
		return notify_fail("����ϼ���졹��ʱ�رգ��볢��tongxin��\n");
        if (!objectp(weapon = me->query_temp("weapon"))
                || ((string)weapon->query("skill_type") != "sword" && !me->is_manmade_npc()))
                        return notify_fail("��������ʹ����ô��ʹ����ϼ���졹��\n");

        if(!wizardp(me) && me->query("family/family_name")!="��˿��")
		return notify_fail("������͵���Ĺ���?��ʼ�ռǲ������γ��֣�\n");

        if( !me->is_fighting(target)|| !living(me) )
                return notify_fail("����ϼ���졹ֻ����ս����ʹ�á�\n");

        if( (int)me->query("max_force") < 1200 )
                return notify_fail("���������Ϊ�������ߣ�\n");

        if( (int)me->query("force") < skill+100 )
                return notify_fail("�����ڵ��������㣡\n");
	if (me->query_temp("mantian_busy")) 
		return notify_fail("�����ö�Ͳ����ˡ�\n");
        if( skill < 100)
                return notify_fail("����ϼ��������Ϊ����������ʹ�á���ϼ���졹! \n");

        if( skill2 < 100)
                return notify_fail("������ľ�����Ϊ����������ʹ�á���ϼ���졹! \n");

        if( me->query_skill_mapped("sword") != "qingxia-jian") 
                return notify_fail("��û�м�����ϼ�������޷�ʹ�á���ϼ���졹��\n");
 	/*
        if (skill<180 && me->query_str()>100)
        {
                msg = HIY "$N��Ȼ���������������������ὣ����ʱ�������ѣ����磭��
                \n"HIC"����ϼ���졻
                \n"HIY"����������Ƭ����ǵ���$n�����ȥ��\n\n"NOR;
                message_vision(msg, me, target);
                ob = me->query_temp("weapon");
// �������װ���Ĳ������౦������ô���еĽ���û��
// ע����������౦��d/pansi/obj/ziqing.c�ļ��в���
// set("no_break", 1);                
        if( (string)weapon->query("id")!="ziqing sword" && !me->is_manmade_npc() )
                destruct(ob);
 
                ap = ((me->query("combat_exp"))*(me->query_spi()));
                dp = ((target->query("combat_exp"))*(target->query_spi()))/2;

                if( dp < 1 )
                        dp = 1;
                if( random(ap) > dp )
                {
                        msg = HIR "$n��ǰ�·�ӿ��������ɫϼ�⣬���֮�£�������Ƭ��ȻǶ����$n�����ϣ�\n\n$n�ҽ�һ��������¶����Ϊʹ��ı��顣\n\n"NOR;
                        message_vision(msg, me, target);
                        kee_wound = 100 + skill + random(skill*2);

                        if(kee_wound > target->query("kee")) kee_wound = (target->query("kee") + 1);
                        target->add("kee", -kee_wound);
                        target->add("eff_kee", -(kee_wound/4));
                        COMBAT_D->report_status(target, 0);
                        me->start_busy(1+random(2));
                        me->add("force",-250);
                }
                else
                {
                        msg = HIG "ֻ��$n���ҵ�������һ��ؼ��ɳ��죬���������������Ľ�Ƭ��\n\n"NOR;
                        message_vision(msg, me, target);
                        me->start_busy(3);
                        me->add("force",-100);
                }

                call_out("perform_qiao", 10, me);
                return 1;
        }
        else if(skill<180 && me->query_str()<100 )
        {
                msg = HIW "$N��Ȼ���������������һ���Ҫʩչ��ϼ�������Ͼ���֮һ�ġ���ϼ���족��
                \nȴ���Ϲ������㣬��Ȼû����������"+weapon->query("name")+HIW"��\n" NOR;
                msg += HIR "$n��Ҫ������ͻȻ���ֻ����ѵã���ʱ������������\n\n";
                message_vision(msg, me, target);
                me->add("force",-50);
                me->start_busy(1+random(2));
        }
        else
        {*/
                msg = HIW "$NͻȻ���������������"+weapon->query("name")+HIW"�����罣â���£�����һ�񣬾�Ȼʹ������ϼ�����ܴ�����
\n"HIC"��������ϼ��â������
\n"HIW"��㽣â�����ӿ���������壬��������������$n��\n\n" NOR;
                message_vision(msg, me, target);

                ap = me->query("combat_exp")/10000;
                dp = target->query("combat_exp")/10000;
		ap =  ap + dp;
		if( target->is_busy() ) dp = dp/2;
                if( dp < 1 )
                        dp = 1;
                wound = 0;
                if( random(ap) > dp*2/3 )
                {
                        msg = HIR "$n�Ը�������Ȼ�����޲ߣ������âǡ��������Ƭ������$n�����ϣ�\n\n$n�ҽ�һ��������¶����Ϊʹ��ı��顣\n\n"NOR;
                        message_vision(msg, me, target);
                        damage = skill*2 + random(skill2 + me->query("force_factor"));
                        target->receive_damage("kee",damage,me);
                        damage = damage - target->query_temp("apply/armor");
                        if( damage > 0 )
                        {
       				damage = damage/2+random(damage)/3;
       				target->receive_wound("kee",damage,me);
       				wound=1;
       			}
                        COMBAT_D->report_status(target, wound);
                        //me->start_busy(1 + random(2));
                        me->add("force",-skill/2-random(skill2)/2);
                }
                else
                {
                        msg = HIG "$n��Ȼ������������һ��ؼ��ɳ��죬���������������Ľ�â��\n\n"NOR;
                        message_vision(msg, me, target);
                        //me->start_busy(2);
                        me->add("force",-100);
                }
		me->set_temp("mantian_busy",1);
    		call_out("remove_effect",3+random(3),me);
                return 1;
        //}

        return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("mantian_busy");
} 

int perform_qiao(object me)
{
        object weapon, target;
        target = me->select_opponent();
        if(me->is_fighting() && living(target) && living(me) && (!objectp(weapon = me->query_temp("weapon"))))
        {
                object qiao;
                string msg;
                int count;
                qiao = new("/d/pansi/obj/qiao");
                qiao->move(me);
                qiao->wield();
                count = me->query_spi();
                me->add_temp("apply/dodge", count * 3); 
                count = me->query_str();
                me->add_temp("str", count * 2); 
                msg = HIY "\n$NͻȻ�����Ͻ������õ����У���ʽͻȻ���٣�����㹥�����У���ͻȻ�ı仯��$nĿ�ɿڴ���\n\n"NOR;
                message_vision(msg, me, target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                me->delete_temp("apply/dodge", count * 3);
                me->delete_temp("str", count * 2);
        }
        return 1;
}

