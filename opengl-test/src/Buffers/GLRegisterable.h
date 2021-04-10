#pragma once

/// <summary>
/// A type that is registrable into opengl.
/// </summary>
class GLRegisterable
{
public:
	virtual ~GLRegisterable() = default;

	/// <summary>
	/// Binds the object to opengl statemachiene.
	/// </summary>
	virtual void Bind() const = 0;

	/// <summary>
	/// Unbinds the object to opengl statemachiene.
	/// </summary>
	virtual void Unbind() const = 0;

	/// <summary>
	/// Returns the opengl id for this object.
	/// </summary>
	/// <returns></returns>
	virtual unsigned int Id() const { return _registerId; }

protected:
	unsigned int _registerId = -1;
};
