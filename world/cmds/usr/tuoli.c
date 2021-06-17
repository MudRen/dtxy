// by gslxz@mhsj 1/7/2001
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string banghui,msg;
	object lingpai;
	if(me->is_fighting()||me->is_busy())
		return notify_fail("����æ���ء�\n");
	if(! (banghui=me->query("banghui")))
		return notify_fail("��û�вμ��κΰ�ᣬ�������롣\n");
	if(! arg)
		return notify_fail("��Ҫ����ʲô��᣿\n");
	if(arg != banghui)
		return notify_fail("�㲻��������ĳ�Ա��\n");
        lingpai=new("/obj/lingpai");
        lingpai->create(banghui);
        if(lingpai->query("no_use"))    {
                destruct(lingpai);
                return notify_fail("��İ���ļ������⣬������ʦ��ϵ��\n");
        }
	if(me->query("id")==lingpai->query("bangzhu_id"))	{
		msg="���ǰ�ᡸ"+me->query("banghui")+"���İ���������ǰ���ָ�����ΰ�����\n";
	}
	else	msg="���ǰ�ᡸ"+me->query("banghui")+"���İ��ڡ�\n";
	msg +="�����Ҫ������(y/n)��";
	write(msg);
	destruct(lingpai);
	input_to("yes_or_no",me,banghui);
	return 1;
}

// by gslxz@mhsj 1/7/2001
int yes_or_no(string str,object me,string banghui)
{
	mapping data;
	object lingpai;
	str=lower_case(str);
	if(str=="y"||str=="yes")	{
		lingpai=new("/obj/lingpai");
		lingpai->create(banghui);
		if( lingpai->query("no_use"))	{
			destruct(lingpai);
			return notify_fail("��İ���ļ������⣬������ʦ��ϵ��\n");
		}
		if(userp(me))	data=lingpai->query("player");
		else	data=lingpai->query("npc");
		if(! mapp(data))	data=([]);
		map_delete(data,me->query("id"));
		if(userp(me))	lingpai->set("player",data);
		else	lingpai->set("npc",data);
		if(me->query("id")==lingpai->query("bangzhu_id"))	{
			lingpai->set("bangzhu_id","???");
			lingpai->set("bangzhu","???");
		}

       message("channel:rumor",YEL"�����������"+me->query("name")+"����"+
                "��ᡸ"HIW+banghui+NOR+YEL"����\n"NOR,users());
	me->delete("banghui");
	if(!undefinedp(me->query("score")))
		me->delete("score");
	if(!undefinedp(me->query("bh_rank")))
		me->delete("bh_rank");
	if(!undefinedp(me->query("rank_lv")))
		me->delete("rank_lv");
	if(!undefinedp(me->query("title")))
		me->set("title",NOR+banghui+"��ͽ"NOR);
       me->save();
	lingpai->save();
	if(! sizeof(lingpai->query("player")) && 
		! sizeof(lingpai->query("npc")))	{
		rm("/data/guild/"+banghui+".o");
		message("channel:rumor",YEL"�������������ᡸ"HIW+banghui+NOR+YEL
                        "�������߽��ˣ�\n"NOR,users());
	}
	destruct(lingpai);
	return 1;
	}
	write("�ðɣ��������������������\n");
	return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ��tuoli <�������>
���ָ�����ʹ�������ᡣ
ǰ����������Ǹð���Ա��
HELP
        );
        return 1;
}
