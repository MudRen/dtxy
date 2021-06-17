//JackyBoy Write these Functions for CCTX's TOPTEN!
//Updated in 1999/3/8

#include <ansi.h>
#include <mudlib.h>

void topten_checkplayer(object);
int get_all_data(object,string);
int topten_del(string,string);
int topten_add(object,string);
int topten_save(string,string,string);
string topten_query(string);
string query_type();


void topten_checkplayer(object player)
{//������ò�����������컹�Ǻ����أ�������Щ����Ҫ�е����ֵģ�������Ů�Ա�
	topten_add(player,"rich");
	topten_add(player,"pker");
	topten_add(player,"kill");
	topten_add(player,"spells");
	topten_add(player,"exp");
	topten_add(player,"daoxing");
	topten_add(player,"force");
	topten_add(player,"per1");
	topten_add(player,"per2");
	topten_add(player,"age");
	topten_add(player,"qn");
	topten_add(player,"rker");
	return;
}

string query_type()
{
	return HIY+CHINESE_MUD_NAME+"�������������͵����а�\n"+
		HIC"rich\t"HIW+RICH_B+"\n"+
		HIC"exp\t"HIW+EXP_B+"\n"+
		HIC"daoxing\t"HIW+DAOXING_B+"\n"+
		HIC"pker\t"HIW+PKER_B+"\n"+
		HIC"force\t"HIW+neili_B+"\n"+
		HIC"kill\t"HIW+SHEN1_B+"\n"+
		HIC"spells\t"HIW+SHEN2_B+"\n"+
		HIC"per1\t"HIW+PER1_B+"\n"+
		HIC"per2\t"HIW+PER2_B+"\n"+
		HIC"age\t"HIW+AGE_B+"\n"+
		HIC"qn\t"HIW+POTENTIAL_B+"\n"+
		HIC"rker\t"HIW+RKER_B+"\n"+
		NOR;
}
int topten_save(string f_name,string b_name,string str)
{
	string *astr;
	int i;
	astr=explode(str,"\n");
	str="";
	for(i=0;i<sizeof(astr)&&i<10;i++)
		str+=astr[i]+"\n";
	if(!write_file(f_name,str,1))
		return notify_fail("�޷�д�ļ�"+f_name+"��Ȩ�޲���!���ܸ���"+b_name+"!\n");
	return 1;
}

string topten_query(string type)
{
	string b_name,f_name,str,*astr,*bstr,name,id;
	int i,j,data;
	switch(type)
	{
		case "rich":
			b_name=RICH_B;
			f_name=TOPTEN_RICH;
			break;
		case "pker":
			b_name=PKER_B;
			f_name=TOPTEN_PKER;
			break;
		case "exp":
			b_name=EXP_B;
			f_name=TOPTEN_EXP;
			break;
		case "daoxing":
			b_name=DAOXING_B;
			f_name=TOPTEN_DAOXING;
			break;
		case "qn":
			b_name=POTENTIAL_B;
			f_name=TOPTEN_POTENTIAL;
			break;
		case "kill":
			b_name=SHEN1_B;
			f_name=TOPTEN_SHEN1;
			break;
		case "spells":
			b_name=SHEN2_B;
			f_name=TOPTEN_SHEN2;
			break;
		case "force":
			b_name=neili_B;
			f_name=TOPTEN_neili;
			break;
		case "age":
			b_name=AGE_B;
			f_name=TOPTEN_AGE;
			break;
		case "per1":
			b_name=PER1_B;
			f_name=TOPTEN_PER1;
			break;
		case "per2":
			b_name=PER2_B;
			f_name=TOPTEN_PER2;
			break;
		case "rker":
			b_name=RKER_B;
			f_name=TOPTEN_RKER;
			break;
		default:
			return "û��"+type+"�������а�\n";
	}
	if(file_size(f_name)==-1)
		return b_name+"�������ļ���û�д�����\n";
	astr=explode(read_file(f_name),"\n");
	str=HIY+CHINESE_MUD_NAME+"��\n"NOR+HIC+b_name+"\n";
	for(i=0;i<sizeof(astr);i++)
	{
		bstr=explode(astr[i],";");
		str+=HIC"���е�"+chinese_number(i+1)+"��"HIW;
		for(j=0;j<sizeof(bstr);j++)
		{
			if(sscanf(bstr[j],"%s(%s)%d",name,id,data)!=3)
				return "���ݴ���!�ļ���"+f_name+"��"+i+"�е�"+j+"�\n"+
					"�������ݣ�"+bstr[j]+"\n";
			str+=name+"("+id+")";
			if (type=="rker")
				str+=" (" + data + ")\t";
		}
		str+="\n"NOR;
	}
	return str;
}
int get_all_data(object player,string type)
{
	int total, i;
	switch(type)
	{
		case "rich":
			total=(int)player->query("balance")/10000 + player->query("c_balance")/10000 + player->query("g_balance");
			break;
		case "pker":
			total=(int)player->query("PKS");
			break;
		case "exp":
			total=(int)player->query("combat_exp");
			break;
		case "daoxing":
			total=(int)player->query("daoxing");
			break;
		case "qn":
			total=(int)player->query("potential")-
			      (int)player->query("learned_points") + player->query("c_potential");
			break;
		case "kill":
			total=(int)player->query("PKS")+(int)player->query("MKS");
			break;
		case "spells":
			total=(int)player->query("max_mana");
			break;
		case "force":
			total=(int)player->query("max_force");
			break;
		case "age":
			total=(int)player->query("mud_age");
			break;
		case "per1":
			if (player->query("gender")!="����")
				total=-1;
			else total=player->query_per();
			break;
		case "per2":
			if (player->query("gender")!="Ů��")
				total=-1;
			else total=player->query_per();
			break;
		case "rker":
                        total = 0;
			for ( i = 0; i < 20; i++ ) {
                            int count;
                            int factor;
                            count = player->query("rzr_killed_lvl" + i, 0);
                            switch(i) {
                                case 0:
                                    factor = 1;
                                    break;
                                case 1:
                                    factor = 2;
                                    break;
                                case 2:
                                    factor = 4;
                                    break;
                                case 3:
                                    factor = 16;
                                    break;
                                case 4:
                                default:
                                    factor = 32 + 32 * (i - 4);
                                    break;
                            }
			    total += count * factor;
                        }
			break;
		default:
			total=-1;//��-1��־���ͳ���
	}
	return total;
}

int topten_del(string pid,string type)
{
	string str,*astr,*bstr,name,id,b_name,f_name;
	int i,j,k,money;
	switch(type)
	{
		case "rich":
			b_name=RICH_B;
			f_name=TOPTEN_RICH;
			break;
		case "pker":
			b_name=PKER_B;
			f_name=TOPTEN_PKER;
			break;
		case "exp":
			b_name=EXP_B;
			f_name=TOPTEN_EXP;
			break;
		case "daoxing":
			b_name=DAOXING_B;
			f_name=TOPTEN_DAOXING;
			break;
                case "qn":
                        b_name=POTENTIAL_B;
                        f_name=TOPTEN_POTENTIAL;
                        break;
		case "kill":
			b_name=SHEN1_B;
			f_name=TOPTEN_SHEN1;
			break;
		case "spells":
			b_name=SHEN2_B;
			f_name=TOPTEN_SHEN2;
			break;
		case "force":
			b_name=neili_B;
			f_name=TOPTEN_neili;
			break;
		case "age":
			b_name=AGE_B;
			f_name=TOPTEN_AGE;
			break;
		case "per1":
			b_name=PER1_B;
			f_name=TOPTEN_PER1;
			break;
		case "per2":
			b_name=PER2_B;
			f_name=TOPTEN_PER2;
			break;
		case "rker":
			b_name=RKER_B;
			f_name=TOPTEN_RKER;
			break;
		default:
			return notify_fail("û��"+type+"�������а�\n");
	}
	if(file_size(f_name)==-1)
		return notify_fail(b_name+"��û�д�����\n");
	str=read_file(f_name);
	astr=explode(str,"\n");
	for(i=0;i<sizeof(astr);i++)
	{
		if(strsrch(astr[i],pid)!=-1)//���а���id��Ϊ��
		{
			if(strsrch(astr[i],";")==-1)
			//Ϊ���ʾ����ֻ��һ��id����pid
			{
				str="";
				for(j=0;j<sizeof(astr);j++)
					if(j!=i)
						str+=astr[j]+"\n";
				return topten_save(f_name,b_name,str);
			}
			else
			{
				bstr=explode(astr[i],";");
				for(j=0;j<sizeof(bstr);j++)
					if(strsrch(bstr[j],pid)!=-1)//˵�����pid,Ӧ��ȥ��
					{
						astr[i]="";
						for(k=0;k<sizeof(bstr);k++)
							if(k!=j)
							{
								if((k+1)!=sizeof(bstr)
									&&!((j+1)==sizeof(bstr)&&j==(k+1))
								)
									astr[i]+=bstr[k]+";";
								else
									astr[i]+=bstr[k];
							}
						//����ȥ����j��ѭ��Ӧ��ֹͣ,���ǲ�Ӱ����
					}
				str=implode(astr,"\n");
				return topten_save(f_name,b_name,str);
			}
		}
	}
	return 1;
}

int topten_add(object player,string type)
{
	string str,name,id,str1,b_name,f_name;
	string *astr;
	int i,j,data;
	if(wizardp(player))//��ֹ��ʦ�μ����а�
		return 0;
	switch(type)
	{
		case "rich":
			b_name=RICH_B;
			f_name=TOPTEN_RICH;
			break;
		case "pker":
			b_name=PKER_B;
			f_name=TOPTEN_PKER;
			break;
		case "exp":
			b_name=EXP_B;
			f_name=TOPTEN_EXP;
			break;
		case "daoxing":
			b_name=DAOXING_B;
			f_name=TOPTEN_DAOXING;
			break;
                case "qn":
                        b_name=POTENTIAL_B;
                        f_name=TOPTEN_POTENTIAL;
                        break;
		case "kill":
			b_name=SHEN1_B;
			f_name=TOPTEN_SHEN1;
			break;
		case "spells":
			b_name=SHEN2_B;
			f_name=TOPTEN_SHEN2;
			break;
		case "force":
			b_name=neili_B;
			f_name=TOPTEN_neili;
			break;
		case "age":
			b_name=AGE_B;
			f_name=TOPTEN_AGE;
			break;
		case "per1":
			b_name=PER1_B;
			f_name=TOPTEN_PER1;
			break;
		case "per2":
			b_name=PER2_B;
			f_name=TOPTEN_PER2;
			break;
		case "rker":
			b_name=RKER_B;
			f_name=TOPTEN_RKER;
			break;
		default:
			return notify_fail("û��"+type+"�������а�\n");
	}
	if(!objectp(player)||!userp(player))
		return 0;
	if(file_size(f_name)==-1)
	{
		str=player->query("name")+"("+player->query("id")+")"+
			get_all_data(player,type);
		return topten_save(f_name,b_name,str);
	}
	//��Ҫ����
	if(get_all_data(player,type)==-1)
		return notify_fail("���ݲ�ѯ���󣬿����ǲ�ѯ���ʹ���\n");
	if(get_all_data(player,type)==0)
		return 0;
	//Ӧ�����ų���player��id!
	topten_del(player->query("id"),type);
	str=read_file(f_name);
	astr=explode(str,"\n");
	i=0;
	while(i<sizeof(astr))
	{
		if(sscanf(astr[i],"%s(%s)%d",name,id,data)!=3)
			if(sscanf(astr,"%s(%s)%d;%*s",name,id,data)!=3)
				return notify_fail(b_name+"�ļ����ݴ����������ʦ��\n");
		str="";
		if(data<(int)get_all_data(player,type))
		{
			//�������룬��ʱû������������ʮ�У�
			for(j=0;j<sizeof(astr);j++)
			{
				if(j==i)
					str+=player->query("name")+"("+player->query("id")+")"+
						get_all_data(player,type)+"\n";
				str+=astr[j]+"\n";
			}
			return topten_save(f_name,b_name,str);
		}
		else
		if(data==(int)get_all_data(player,type))
		{
			//���ż���
			for(j=0;j<sizeof(astr);j++)
			{
				if(j==i)
					str+=astr[j]+";"+player->query("name")+
						"("+player->query("id")+")"+get_all_data(player,type)+"\n";
				else
					str+=astr[j]+"\n";
			}
			return topten_save(f_name,b_name,str);
		}
		i++;
	}
	if(sizeof(astr)<10)
	{
		str=implode(astr,"\n")+"\n"+player->query("name")+"("+player->query("id")+
			")"+get_all_data(player,type);
		return topten_save(f_name,b_name,str);
	}
	return 0;
}
