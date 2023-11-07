#pragma once
#include<string>
#include<vector>
#include"Fbx.h"
#include"Transform.h"

using std::string;
using std::vector;

namespace Model
{
	struct ModelData
	{
		//FBX
		Fbx* pfbx_;
		//トランスフォーム
		Transform Transform_;
		//ファイル名
		string mFileName_;
	};

	//モデルをロード
	//引数：fileName　ファイル名
	//戻値：そのモデルデータに割り当てられた番号
	int Load(std::string fileName);

	//ワールド行列を設定
	//引数：hModel	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetTransform(int hModel, Transform& transform);

	//描画
	//引数：hModel	描画したいモデルの番号
	//引数：matrix	ワールド行列
	void Draw(int hModel);

	void Release();
}