// by gslxz@mhsj 1/7/2001
inherit F_CLEAN_UP;
int check_name(string name);

int main(object me, string arg)
{
	object ob,lp;
	string name,id;
	string banghui;

	if(! arg)	return notify_fail("ָ���ʽ��renming <ĳ��> <ְ��>\n");
	if(! stringp(banghui=me->query("banghui")))
			return notify_fail("ֻ�а�������ʹ�ñ����\n");
	lp=new("/obj/lingpai");
	lp->create(banghui);
	if(lp->query("no_use"))	{
		destruct(lp);
		return notify_fail("��İ���ļ������⣬������ʦ��ϵ��\n");
	}
	if(lp->query("bangzhu_id")!=me->query("id"))	{
		destruct(lp);
		return notify_fail("ֻ�а�������ʹ�ñ�ָ�\n");
	}
	destruct(lp);
	if(sscanf(arg,"%s %s",id,name)==2)	{
		ob=present(id,environment(me));
		if(! ob)	return notify_fail("���û����ô���ˡ�\n");
		if(! ob->is_character())
				return notify_fail("��������ǲ������ˣ�\n");
		if(!userp(ob))	return notify_fail("��ֻ�Ա��������ʹ���������\n");
		if(banghui!=(string)ob->query("banghui"))
				return notify_fail("��ֻ�Ա��������ʹ���������\n");
		if(me->is_busy()||me->is_fighting())
				return notify_fail("����æ���أ�\n");
		if(ob->is_busy()||ob->is_fighting())
				return notify_fail("�Է���æ���أ�\n");
		if(! check_name(name))
				return notify_fail("��������ְ����������ģ���Ϊ�������֣�\n");
		ob->set("bh_rank",name);
		message_vision("$N����$nΪ��"+banghui+"��"+name+"��\n",me,ob);
		return 1;
	}
	else	return notify_fail("ָ���ʽ��renming <ĳ��> <ְ��>\n");
}
// by gslxz@mhsj 1/7/2001

int check_name(string name)
{
        int i;

        i = strlen(name);

        if( (strlen(name) < 4) || (strlen(name) > 16 ) ) {
		return 0;
	}
        while(i--) {
                if( name[i]<=' ' ) {
			return 0;
		}
	if( i%2==0 && !is_chinese(name[i..<0]) ) {
			return 0;
	}
	}
	return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ��renming <player's id> <ְ������>

����ָ������Ұ��İ���ר���������Ϊ�����
����Ұ��ڷ�����ְ����̳����������������ʹ
�ߵȳ�ν��
ע�⣺��������Ϊ����������ң����Դ��������ʹ
����(yaoqing)��Ȩ����
HELP
        );
        return 1;
}


