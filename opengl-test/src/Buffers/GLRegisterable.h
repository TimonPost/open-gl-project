#pragma once

class GLRegisterable
{
public:
	virtual ~GLRegisterable() = default;
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual unsigned int Id() const { return _registerId; }

protected:
	unsigned int _registerId;
};
