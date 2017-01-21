/*���˼�룺
	�Ȱ������һ����ʽת���ɺ�׺���ʽ��Ȼ�������׺���ʽ����������

	�������������������������
	������������	 ���ջ�գ�ѹջ
				 ջ���գ��Ƚϸ�Ԫ�غ�ջ��Ԫ�ص����ȼ��������ǰԪ�����ȼ����ڻ��ߵ��� ջ��Ԫ�����ȼ�����ô�����
				 ������ջ��Ԫ�ء���Ԫ��ѹ��(����ǡ�����Ҳѹ��)
						�����ǰԪ�����ȼ�����ջ��Ԫ�����ȼ���ֱ��ѹջ
			�ַ���ȫ������֮�����ջ���գ����������������ջ����
*/

/*������*/
bool isOperator(const char& chr);//�ж��ǲ��ǲ����� 
bool isLowerEqualThan(const char& top, const char& current)//�жϵ�ǰ�ķ��ź�ջ���������ȼ�
int isLower(const char& top, const char& current); //�ڲ����� 
string toSuffix(const string& infixStr);//����׺ת���ɺ�׺

bool isOperator(const char& chr)
{
	return chr == '(' || chr == ')' || chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '^';
}

int isLower(const char& top, const char& current)
{
	int level[256] = { 0 };
	level['^'] = 3;//���ȼ�
	level['+'] = level['-'] = 1;//
	level['*'] = level['/'] = 2;//

	return level[current] - level[top];//���ز�ֵ
}

bool isLowerEqualThan(const char& top, const char& current)
{
	if (isLower(top, current) <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

string toSuffix(const string& infixStr)//����׺ת���ɺ�׺
{
	string outStr;
	List<char> operatorStack;//װ�������ջ

	for (int i = 0; i < (int)infixStr.size(); ++i)
	{
		if (isOperator(infixStr[i]))//����ǲ������Ļ�
		{
			if (operatorStack.empty())
			{
				operatorStack.push_back(infixStr[i]);//ջ�� ֱ��ѹջ
			}
			else //ջ����
			{
				if (infixStr[i] == '(')//�����"(",ֱ��ѹ��
				{
					operatorStack.push_back(infixStr[i]);
				}
				else if (infixStr[i] == ')')
				{
					while (operatorStack.back() != '(')//������������ź�ջ��Ԫ�ز���(����һֱ����ջ��ֱ����
					{
						outStr += operatorStack.back();//һ��һ���ļӵ�����ַ���
						operatorStack.pop_back();
					}
					//��ʱջ����"("
					operatorStack.pop_back();//ֱ�ӵ���
				}
				else if (isLowerEqualThan(operatorStack.back(), infixStr[i]))//�Ƚ�ջ��Ԫ�غ͵�ǰԪ��,�����ǰԪ��
					//С�ڵ���ջ��:
				{
					outStr += operatorStack.back();//�����ջ��Ԫ��
					operatorStack.pop_back();//Ȼ�󵯳�ջ��Ԫ��
					operatorStack.push_back(infixStr[i]);//�ٽ���ǰԪ��ѹ��ջ��;
				}
				else//�����ǰԪ�ر�ջ��Ԫ�����ȼ��ߵĻ�����ѹջ
				{
					operatorStack.push_back(infixStr[i]);
				}
			}
		}
		else //����ǲ������Ļ�
		{
			outStr += infixStr[i];//�ͰѸò����������������
		}
	}

	while (!operatorStack.empty())
	{
		outStr += operatorStack.back();
		operatorStack.pop_back();
	}
	return outStr;
}
