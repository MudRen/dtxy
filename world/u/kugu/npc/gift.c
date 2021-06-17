//����ʹ�ߣ���д���򵥵�
inherit NPC;
#include <ansi.h>

mixed attr_list = ({"int", "str", "con", "spi", "per", "kar", "cps", "cor"});

int give_gift();
int give_08gift();
int give_seven();
int remove_questfail();
int give_2013();
int give_christmas();
int give_chunjie();
void create()
{
	set_name("����ʹ��", ({"liwu shizhe","shizhe"}));
   	set ("long", @LONG

��������ʹ�ߣ����ȥ����(ask)����������(gift)����Ϣ��
LONG);
	set("gender", "Ů��");
    	set("title",HIM"�����߱�����"NOR);
        set("age", 21);
        set("per", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
	set("inquiry", ([
		"���ܻ���һ":(:give_gift:),
		"���ܻ����":(:give_08gift:),
		//"��Ϧ":(:give_seven:),
		//"Ԫ��":(:give_2013:),
		//"ʥ������":(:give_christmas:),
		"���ڿ���":(:give_chunjie:),
	]));
        setup();
}

string get_chinese_gift(string gift) {
        switch(gift) {
                case "int":
                        return "����";
                        break;
                case "str":
                        return "����";
                        break;
                case "con":
                        return "����";
                        break;
                case "spi":
                        return "����";
                        break;
                case "per":
                        return "��ò";
                        break;
                case "kar":
                        return "��Ե";
                        break;
                case "cps":
                        return "����";
                        break;
                case "cor":
                        return "����";
                        break;
                default:
                        return "����ʶ" + gift;
                        break;
        }
}

int remove_questfail()
{
	object who = this_player();
	int f = 0;
switch (who->query("family/family_name"))
        {
        	case "�ݿ�ɽ�޵׶�":
                { 
                	if( who->query("daojian_cant") )
                	{
                		who->delete("daojian_cant");
                		f = 1;
                	}
                        break;
		}
		case "������":
                { 
                	if( who->query("kai_cant") )
                	{
                		who->delete("kai_cant");
                		f = 1;
                	}
                        break;
		}
		case "��ׯ��":
                { 
                	if( who->query("wuxing_cant") )
                	{
                		who->delete("wuxing_cant");
                		f = 1;
                	}
                        break;
		}
		case "���ƶ�":
                { 
                	if( who->query("huohun_cant") )
                	{
                		who->delete("huohun_cant");
                		f = 1;
                	}
                        break;
		}
		case "�Ϻ�����ɽ":
                { 
                	if( who->query("fmtd_cant") )
                	{
                		who->delete("fmtd_cant");
                		f = 1;
                	}
                        break;
		}
		case "���޵ظ�":
                { 
                	if( who->query("jingtian_cant") )
                	{
                		who->delete("jingtian_cant");
                		f = 1;
                	}
                        break;
		}
		case "��ѩɽ":
                { 
                	if( who->query("piaoxue_cant") )
                	{
                		who->delete("piaoxue_cant");
                		f = 1;
                	}
                        break;
		}
		case "��������":
                { 
                	if( who->query("cfpl_cant") )
                	{
                		who->delete("cfpl_cant");
                		f = 1;
                	}
                        break;
		}
		case "����ɽ���Ƕ�":
                { 
                	if( who->query("fangcun/panlong_qiansi_finish") == 1 && who->query("fangcun/panlong_noway") )
                	{
                		who->delete("fangcun/panlong_qiansi_finish");
                		who->delete("fangcun/panlong_noway");
                		f = 1;
                	}
                	else if( who->query("fangcun/panlong_nowaylingtai") )
                	{
                		who->delete("fangcun/panlong_nowaylingtai");
                		f = 1;
                	}
                        break;
		}
		case "��˿��":
                { 
                	if( who->query("qingyun_cant") )
                	{
                		who->delete("qingyun_cant");
                		f = 1;
                	}
                        break;
		}
		case "����ɢ��":
                { 
                	if( who->query("icefire_cant") )
                	{
                		who->delete("icefire_cant");
                		f = 1;
                	}
                        break;
		}
		case "�¹�":
                { 
                	if( who->query("jueqing_cant") )
                	{
                		who->delete("jueqing_cant");
                		f = 1;
                	}
                	else if( who->query("jueqing_known") ==2 && !who->query("accept/sun") )
                	{
                		who->set("can_go_sun",1);
                		f = 1;
                	}
                        break;
		}
		case "����ɽ���鶴":
                { 
                	if( who->query("quzhu_cant") )
                	{
                		who->delete("quzhu_cant");
                		f = 1;
                	}
                        break;
		}
		case "��ɽ��":
                { 
                	if( who->query("sword_cant") )
                	{
                		who->delete("sword_cant");
                		f = 1;
                	}
                        break;
		}
	}
	return f;
}

int give_gift()
{
	object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say С������ȥ���������");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 1000000 )
	{
		command("say ����Ϊ�������ܲ���������");
	  	return 1;
	}
	if( who->query("gift/20061001") == "got" )
	{
		message_vision("$N����$n����һ����\n",this_object(),this_player());
	       	command("say ����ֻ��һ�ݣ�����Ͳ��ٸ��ˣ�");
	  	return 1;
	}
	f = remove_questfail();
	if( f )
	{
		who->set("gift/20061001","got");
		message_vision(HIR"$N��һָ��$n���쵽���巢����һЩ����ı仯��\n"NOR,this_object(),who);
		return 1;
	}
	message_vision(HIR"$N��ָһ�㣬���յĶ�$n˵��������ûʧ�ܣ�Ҫʲô���\n"NOR,this_object(),who);
	return 1;
}

int give_08gift()
{
	object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say С������ȥ���������");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
	{
		command("say ����Ϊ�������ܲ���������");
	  	return 1;
	}
	if( who->query("gift/20080101") == "got" )
	{
		message_vision("$N����$n����һ����\n",this_object(),this_player());
	       	command("say ����ֻ��һ�ݣ�����Ͳ��ٸ��ˣ�");
	  	return 1;
	}
	f = remove_questfail();
	if( f )
	{
		who->set("gift/20080101","got");
		message_vision(HIR"$N��һָ��$n���쵽���巢����һЩ����ı仯��\n"NOR,this_object(),who);
		return 1;
	}
	message_vision(HIR"$N��ָһ�㣬���յĶ�$n˵��������ûʧ�ܣ�Ҫʲô���\n"NOR,this_object(),who);
	return 1;
}

int give_seven()
{
	object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say С������ȥ���������");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
	{
		command("say ����Ϊ�������ܲ���������");
	  	return 1;
	}
	if( who->query("gift_exp/20110707") == "got" )
	{
		message_vision("$N����$n����һ����\n",this_object(),this_player());
	       	command("say ����ֻ��һ�ݣ�����Ͳ��ٸ��ˣ�");
	  	return 1;
	}
	f = remove_questfail();
	who->set("gift_exp/20110707","got");
	message("chat",HIC+"\n\n��"+HIW+"��������"+HIC+"������ʹ��(liwu shizhe)��" + who->name() + "ǰ����ȡ��Ϧ�����������ףԸ�����������ճɾ�����\n\n"NOR,users());
	if( f )
	{
		message_vision(HIR"$N��$n˵������������ף����Ϧ���֣��������ϴ�����ܻ���һ�Ρ�\n"NOR,this_object(),who);
		return 1;
	}
	else
	{
		message_vision(HIR"$N��$n˵������ϲ���񹦴�ɣ�������������Ϧ֮�գ��ر�����һ�ݡ�\n"NOR,this_object(),who);
		write(HIY"��õ��ˣ�100����У�100000��ѧ��\n"NOR);
		who->add("daoxing",100000);
		who->add("combat_exp",100000);
	}
	return 1;
}

int give_2013() {

object who=this_player();
	int f = 0;
	if(!userp(who))
	{
		command("hate");
		command("say С������ȥ���������");
		command("qi");
		return 1;
	}
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
	{
		command("say ����Ϊ�������ܲ���������");
	  	return 1;
	}
	if( who->query("gift_exp/20130101") == "got" )
	{
		message_vision("$N����$n����һ����\n",this_object(),this_player());
	       	command("say ����ֻ��һ�ݣ�����Ͳ��ٸ��ˣ�");
	  	return 1;
	}
	f = remove_questfail();
	who->set("gift_exp/20130101","got");
	message("chat",HIC+"\n\n��"+HIW+"��������"+HIC+"������ʹ��(liwu shizhe)��" + who->name() + "ǰ����ȡԪ�������������ף���������֣�\n\n"NOR,users());
	if( f )
	{
		message_vision(HIR"$N��$n˵������������ף��������ֲ��Ҵ�����ܻ���һ�Ρ�\n"NOR,this_object(),who);
		return 1;
	}
	else
	{
		message_vision(HIR"$N��$n˵������ϲ���񹦴�ɣ���������������֮�ʣ��ر�����һ�ݡ�\n"NOR,this_object(),who);
		who->add("daoxing",100000);
		who->add("combat_exp",100000);
                who->add("g_balance",50000);
		who->add("obstacle/rebirth",-1);
                write(HIY"��õ��ˣ�100����У�100000��ѧ��5���Ʊ��1����ë��\n"NOR);
	}
	return 1;
}

int give_christmas()
{
	int f = 0;
	int size, i;
	object who=this_player();
	if(!userp(who))
        {
                command("hate");
                command("say С������ȥ���������");
                command("qi");
                return 1;
        }
	if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
        {
                command("say ����Ϊ�������ܲ���������");
                return 1;
        }
	if( who->query("gift_exp/20121225") == "got" )
        {
                message_vision("$N����$n����һ����\n",this_object(),this_player());
                command("say ����ֻ��һ�ݣ�����Ͳ��ٸ��ˣ�");
                return 1;
        }
	f = remove_questfail();
	who->set("gift_exp/20121225","got");
	message("chat",HIC+"\n\n��"+HIW+"��������"+HIC+"������ʹ��(liwu shizhe)��" + who->name() + "��ȡʥ�������������ף���ʥ�����֣�\n\n"NOR,users());
	if(!random(10))
	{
		size = sizeof(attr_list);
		i = random(size);
		who->add(attr_list[i], 1);
		message("chat",HIC+"\n\n��"+HIW+"��������"+HIC+"������ʹ��(liwu shizhe)��" + who->name() + "�������󽱣�" + HIW + get_chinese_gift(attr_list[i]) + HIC"һ�㣡\n\n"NOR,users());
	}
	if( f )
	{
		message_vision(HIR"$N��$n˵������������ף��ʥ�����ֲ��Ҵ�����ܻ���һ�Ρ�\n"NOR,this_object(),who);
	}
	else
	{
		message_vision(HIR"$N��$n˵������ϲ���񹦴�ɣ���������������֮�ʣ��ر�����һ�ݡ�\n"NOR,this_object(),who);
                who->add("daoxing",100000);
                who->add("combat_exp",100000);
                who->add("g_balance",50000);
                who->add("obstacle/rebirth",-1);
                write(HIY"��õ��ˣ�100����У�100000��ѧ��5���Ʊ��1����ë��\n"NOR);
	}
	return 1;
}

int give_chunjie()
{
        int f = 0;
        int size, i;
        object who=this_player();
        if(!userp(who))
        {
                command("hate");
                command("say С������ȥ���������");
                command("qi");
                return 1;
        }
        if( who->query("combat_exp") + who->query("daoxing") < 2000000 )
        {
                command("say ����Ϊ�������ܲ���������");
                return 1;
        }
        if( who->query("gift_exp/20130209") == "got" )
        {
                message_vision("$N����$n����һ����\n",this_object(),this_player());
                command("say ����ֻ��һ�ݣ�����Ͳ��ٸ��ˣ�");
                return 1;
        }
        f = remove_questfail();
        who->set("gift_exp/20130209","got");
        message("chat",HIC+"\n\n��"+HIW+"��������"+HIC+"������ʹ��(liwu shizhe)��" + who->name() + "��ȡʥ�������������ף��Ҵ��ڿ��֣�\n\n"NOR,users());
        if(!random(7))
        {
                size = sizeof(attr_list);
                i = random(size);
                who->add(attr_list[i], 1);
                message("chat",HIC+"\n\n��"+HIW+"��������"+HIC+"������ʹ��(liwu shizhe)��" + who->name() + "�������󽱣�" + HIW + get_chinese_gift(attr_list[i]) + HIC"һ�㣡\n\n"NOR,users());
        }
        if( f )
        {
                message_vision(HIR"$N��$n˵������������ף�㴺�ڿ��ֲ��Ҵ�����ܻ���һ�Ρ�\n"NOR,this_object(),who);
        }
        else
        {
                message_vision(HIR"$N��$n˵������ϲ���񹦴�ɣ���������������֮�ʣ��ر�����һ�ݡ�\n"NOR,this_object(),who);
                who->add("daoxing",10000);
                who->add("combat_exp",10000);
                who->add("g_balance",50000);
                who->add("potential",1000000);
                write(HIY"��õ��ˣ�10����У�10000��ѧ��5���Ʊ��100��Ǳ�ܡ�\n"NOR);
        }
        return 1;
}

